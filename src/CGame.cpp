/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CGame.h"

using namespace std;

CGame::CGame(shared_ptr<CInterface> &interface)
    : m_Interface ( interface )
{
}

CGame &CGame::operator = (CGame &&game) noexcept {
    std::swap (m_Map, game.m_Map);
    std::swap (m_Players, game.m_Players);
    std::swap (m_Interface, game.m_Interface);
    std::swap (m_Buffer, game.m_Buffer);
    return *this;
}

bool CGame::Init(fstream & input) {

    input.exceptions (ifstream::badbit | ifstream::failbit);

    try {
        if (! LoadMap(input) || !LoadPlayers (input) )
            return false;
    }
    catch (fstream::failure & err){
        return false;
    }

    input.close();
    redrawConsole();
    return true;
}

bool CGame::Tick() {

    CheckCollisions();
    redrawConsole();
    m_Interface->PrintLineText(GAME_MODE, EColors::CYAN);
    if (!TakeTurn())
        return false;
    MovePlayers()
        .Gravity();

    return true;
}

void CGame::redrawConsole() const {

    m_Buffer->DrawMapInBuffer(*m_Map);
    for (auto & player : m_Players )
        player->DrawIntoBuffer (*m_Buffer);
    m_Interface->ClearConsole()
            .PrintBuffer(*m_Buffer);
}

bool CGame::SaveGame(const string & filename) const {

    ofstream newMapFile (SAVED_MAPS_FOLDER + filename);
    newMapFile.exceptions(ofstream::badbit | std::ofstream::failbit);
    if (newMapFile.fail())
        return false;
    try {
        m_Map->SaveMap (newMapFile);
        newMapFile << endl;
        newMapFile << PLAYERS << " " << m_Players.size() << endl << endl;
        for (const auto & player : m_Players){
            player->SavePlayer (newMapFile);
            newMapFile << endl;
        }
    }
    catch ( std::ofstream::failure & error ){
        return false;
    }

    return true;
}

CGame &CGame::Gravity() {

    for ( auto & player : m_Players) {
        CCoord coord (player->GetCoord() );

        if (m_Map->canWalkTrough(coord.getDown())) {
            player->TimeInAir(false);
            if (player->getLastDirection() != EDirection::UP) {
                player->Move(coord);
                player->DrawIntoBuffer(*m_Buffer);
                coord.getDown();
            }
        }

        if (m_Map->isInside(coord) && !m_Map->canWalkTrough(coord)) {
            size_t airTime = player->GetTimeInAir();
            if (airTime > 3)
                player->ReceiveHit(airTime * 25);
            player->TimeInAir(true);
        }
        player->resetDirection();
    }

    try {
        for (size_t i = 0; i < m_Players.size(); ++i)
            for (size_t j = 0; j < m_Players.size(); ++j)
                if (i != j && (m_Players[i]->GetCoord() == m_Players[j]->GetCoord()))
                    TakeFight(*m_Players[i], *m_Players[j]);
    }
    catch (const YouDiedException &){
        throw KilledByMonster();
    }

    return * this;
}

CGame &CGame::CheckCollisions () {

    try {
        for (int i = (int) (m_Players.size() -1) ; i >= 0 ; i--){
            m_Players[i]->ReceiveHit(m_Map->GetField(m_Players[i]->GetCoord()).DealsDamage());
            if ( ! m_Players[i]->isAlive() || ! m_Map->canWalkTrough(m_Players[i]->GetCoord()) )
                m_Players.erase(m_Players.begin() + i);
        }
    }
    catch (const YouDiedException &){
        throw StepInLava ();
    }

    return *this;
}

bool CGame::TakeTurn () {

    for ( auto & player : m_Players ){
        if (! player->TakeTurn (*m_Map)){
            redrawConsole();
            m_Interface->PrintLineText(GAME_PAUSED, EColors::CYAN);
            return false;
        }
    }
    return true;
}

CGame &CGame::MovePlayers() {

    for ( size_t i = 0; i < m_Players.size(); ++i ){
        CCoord toMove = m_Players[i]->coordToMove();
        for ( size_t j = 0; j < m_Players.size(); ++j){
            if ( i != j && ( m_Players[i]->GetCoord() == m_Players[j]->GetCoord()))
                TakeFight ( *m_Players[i], *m_Players[j]);
        }
        if ( m_Map->canWalkTrough(toMove))
            m_Players[i]->Move(toMove);
    }

    return *this;
}

CGame &CGame::TakeFight(CPlayer & first, CPlayer & second) {

    try {
        if (rand() % 2 == 0) {
            while (first.isAlive() && second.isAlive()) {
                first.ReceiveHit(second.Attack());
                if (first.isAlive())
                    second.ReceiveHit(first.Attack());
            }
        } else {
            while (first.isAlive() && second.isAlive()) {
                second.ReceiveHit(first.Attack());
                if (second.isAlive())
                    first.ReceiveHit(second.Attack());
            }
        }
    }
    catch (YouDiedException &){
        throw KilledByMonster();
    }

    return *this;
}

bool CGame::LoadMap(fstream & input) {
    size_t width, height,coordX, coordY;
    int HP;
    char c;
    string message;

    input >> message >> width >> height;
    if (message != MAP_INFO || width > MAX_MAP_WIDTH || width < MIN_MAP_WIDTH
        || height > MAX_MAP_HEIGHT || height < MIN_MAP_HEIGHT )
        return false;

    m_Map = std::make_unique <CMap> (height, width);

    for (size_t i = 0; i < height; ++i){
        for (size_t j = 0; j < width; ++j){
            input >> c >> coordX >> coordY >> HP;
            if ( coordX != i || coordY != j || HP <= 0)
                return false;
            if ( m_Map->isBorder( i , j ) && c != '#' )
                return false;
            if ( ! m_Map->SetField (CCoord (coordX, coordY), c, HP) )
                return false;
        }
    }
    input >> message;
    if (message != END_MAP_INFO)
        return false;
    m_Buffer = std::make_unique<CBuffer>(height, width);
    return true;
}

bool CGame::LoadUser ( fstream & input ) {

    char dir, lastDir;
    CCoord coord (0, 0);
    size_t airTime;
    CStats stats;
    EDirection direction = EDirection::NONE, lastDirection = EDirection::NONE;

    input >> coord.m_X >> coord.m_Y;
    input >> stats.m_Energy >> stats.m_HP >> stats.m_Level >> stats.m_Points >> airTime;
    input >> stats.m_ItemName >> stats.m_SecondItemName;
    input >> dir >> lastDir;

    if ( stats.m_HP <= 0 || stats.m_HP > 100 || stats.m_Level > 10 || stats.m_Energy > 100 || stats.m_Energy < 0
        || !GetDirection(dir, direction) || !GetDirection(lastDir, lastDirection))
        return false;

    if ( !( stats.m_ItemName == PICKAXE && stats.m_SecondItemName == SWORD )
        && !( stats.m_SecondItemName == PICKAXE && stats.m_ItemName == SWORD ) )
        return false;

    if (!m_Map->isInside(coord) || !m_Map->canWalkTrough(coord))
        return false;

    m_Players.push_back(make_unique<CPlayerHuman>(coord, stats, airTime, m_Interface, direction, lastDirection));

    return true;
}

bool CGame::LoadMonster(fstream & input ){

    char dir, lastDir;
    CCoord coord (0, 0);
    size_t airTime, count, damage;
    int HP;
    EDirection direction = EDirection::NONE, lastDirection = EDirection::NONE;

    input >> coord.m_X >> coord.m_Y;
    input >>  HP >> airTime >> count >> damage >> dir >> lastDir;

    if ( HP <= 0 || HP > 500 || damage > 100 || !m_Map->isInside(coord)
        || !m_Map->canWalkTrough(coord))
        return false;
    if ( !GetDirection(dir, direction) || !GetDirection(lastDir, lastDirection))
        return false;

    m_Players.push_back(make_unique<CPlayerMonster>(coord, HP, airTime, direction,
                                                    lastDirection, damage, count));

    return true;
}

bool CGame::LoadPlayers(fstream &input) {
    string message;
    int amount, humanPlayers = 0;
    input >> message >> amount;
    if ( message != PLAYERS || amount <= 0 )
        return false;

    for (size_t i = 0; i < (size_t) amount; ++i){
        string type;
        input >> type;
        if (type == PLAYER_HUMAN){
            humanPlayers++;
            if ( !LoadUser(input) )
                return false;
        }
        else if (type == PLAYER_MONSTER) {
            if (!LoadMonster(input))
                return false;
        }
        else
            return false;
    }
    for (size_t i = 0; i < m_Players.size(); i++) {
        for (size_t j = i + 1; j < m_Players.size(); j++)
            if (m_Players[i]->GetCoord() == m_Players[j]->GetCoord())
                return false;
    }

    if (humanPlayers != 1)
        return false;

    return true;
}

bool CGame::GetDirection(char dir, EDirection & direction){
    switch (dir){
        case 'U' : direction = EDirection::UP; return true;
        case 'N' : direction = EDirection::NONE; return true;
        case 'L' : direction = EDirection::LEFT; return true;
        case 'R' : direction = EDirection::RIGHT; return true;
        default  : return false;
    }
}
