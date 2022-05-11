/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CPlayerHuman.h"

using namespace std;

CPlayerHuman::CPlayerHuman(const CCoord &coord, CStats & stats, size_t airTime, shared_ptr<CInterface> &interface,
                           EDirection direction, EDirection lastDirection)
        : CPlayer ( stats.m_HP, coord, airTime, direction, lastDirection ),
          m_Stats ( stats ),
          m_Interface ( interface )
{
    m_InHand = make_unique <CItem> (m_Stats.m_ItemName);
    m_Second = make_unique <CItem> (m_Stats.m_SecondItemName);
    for (size_t i = 0; i < stats.m_Level -1; ++i){
        m_InHand->LevelUP();
        m_Second->LevelUP();
        m_Stats.m_Armor += 5;
    }
    m_Commands.insert({"a", MoveLeftCommand()});
    m_Commands.insert({"w", JumpCommand()});
    m_Commands.insert({"s", SwapWeapons()});
    m_Commands.insert({"d", MoveRightCommand()});
    m_Commands.insert({"h", HitLeftCommand()});
    m_Commands.insert({"u", HitUpCommand()});
    m_Commands.insert({"j", HitDownCommand()});
    m_Commands.insert({"k", HitRightCommand()});
    m_Commands.insert({"p", PauseCommand()});
    m_Commands.insert({"?", HelpCommand()});
    m_Commands.insert({"b", PlaceBlockCommand()});
    for (const auto & command : m_Commands)
        m_KnownCommands.insert(command.first);
}

CPlayerHuman::CPlayerHuman(const CPlayerHuman &other)
        : CPlayer(other.m_HP, other.m_Coord, other.m_TimeInAir, other.m_Direction, other.m_LastDirection)
{
    m_Stats = other.m_Stats;
    m_InHand = std::make_unique <CItem> (* other.m_InHand);
    m_Second = std::make_unique <CItem> (* other.m_Second);
    m_Interface = other.m_Interface;
    m_Commands = other.m_Commands;
    m_KnownCommands = other.m_KnownCommands;
}

CPlayerHuman &CPlayerHuman::operator = (CPlayerHuman other) {
    std::swap (m_Stats, other.m_Stats);
    std::swap (m_KnownCommands, other.m_KnownCommands);
    std::swap (m_Commands, other.m_Commands);
    std::swap (m_Interface, other.m_Interface);
    std::swap (m_InHand, other.m_InHand);
    std::swap (m_Second, other.m_Second);
    std::swap (m_Direction, other.m_Direction);
    std::swap (m_LastDirection, other.m_LastDirection);
    std::swap (m_TimeInAir, other.m_TimeInAir);
    std::swap (m_Coord, other.m_Coord);
    std::swap (m_HP, other.m_HP);
    return *this;
}

CPlayer &CPlayerHuman::ReceiveHit ( size_t damage ) {
    if ( (int) damage > m_Stats.m_Armor )
        m_HP -= int ( damage - m_Stats.m_Armor );
    if (m_HP <= 0)
        throw YouDiedException ();
    return * this;
}

CPlayerHuman &CPlayerHuman::Healing() {
    if (m_Stats.m_Energy < MAX_ENERGY)
        m_Stats.m_Energy += 5;
    if (m_HP < HUMAN_MAX_HP )
        m_HP += 1;
    return *this;
}

size_t CPlayerHuman::Attack() {

    int damage = m_InHand->Damage();
    if (m_InHand->Type() == SWORD)
        damage *= 2;

    while ( m_Stats.m_Energy - 25 >= 0 ) {
        damage += m_InHand->Damage();
        m_Stats.m_Energy -= 25;
    }
    return damage;
}

char CPlayerHuman::Print() const {
    switch ( m_LastDirection ){
        case EDirection::LEFT:  return '<';
        case EDirection::RIGHT: return '>';
        case EDirection::NONE:  return 'v';
        case EDirection::UP:    return '^';
    }
    return 'v';
}

CStats & CPlayerHuman::UpdateStats() {
    m_Stats.m_ItemName = m_InHand->Type();
    m_Stats.m_ItemDamage = m_InHand->Damage();
    m_Stats.m_SecondItemName = m_Second->Type();
    m_Stats.m_SecondItemDamage = m_Second->Damage();
    m_Stats.m_HP = m_HP;
    return m_Stats;
}

bool CPlayerHuman::TakeTurn( CMap &map ) {
    string command;
    UpdateStats();
    if (m_Stats.m_Points >= m_Stats.m_Level * 1000)
        LevelUP();
    while (true) {
        command = m_Interface->GetCommand(m_KnownCommands);
        if (! (m_Commands.find(command)->second.RunCommand(map))) {
            if (command == "p")
                return false;
            else if (command == "w")
                m_Interface->PromptMessage(CANT_JUMP_WARNING, EColors::BRIGHT_RED);
            else if (command == "h" || command == "j" || command == "k" || command == "u")
                m_Interface->PromptMessage(OUT_OF_ENERGY_WARNING, EColors::BRIGHT_RED);
            else if (command == "b")
                m_Interface->PromptMessage(PLACE_BLOCK_ERROR, EColors::BRIGHT_RED);
        }
        else return true;
    }
}

std::unique_ptr<CPlayer> CPlayerHuman::Clone() const {
    return std::make_unique <CPlayerHuman> (*this);
}

CPlayer &CPlayerHuman::LevelUP() {
    if (m_Stats.m_Level < 10){
        m_Stats.m_Armor += 5;
        m_Stats.m_Level++;
        m_InHand->LevelUP();
        m_Second->LevelUP();
    }
    return *this;
}

void CPlayerHuman::DrawIntoBuffer ( CBuffer & buffer ) {
    buffer.PrintCharInMap(m_Coord, Print());
    buffer.m_Stats = & UpdateStats();
}

void CPlayerHuman::SavePlayer(ofstream &filename) const {
    filename << PLAYER_HUMAN << std::endl;
    filename << m_Coord.m_X << " " << m_Coord.m_Y << std::endl;
    filename << m_Stats.m_Energy << " " << m_Stats.m_HP << " " << m_Stats.m_Level << " ";
    filename << m_Stats.m_Points << " " << m_TimeInAir << std::endl;
    filename << m_Stats.m_ItemName << " " << m_Stats.m_SecondItemName << std::endl;
    filename << CharDirection (m_Direction) << " " << CharDirection(m_LastDirection) << std::endl;
}

CGameCommand CPlayerHuman::MoveLeftCommand() {
    return CGameCommand {
        MOVE_LEFT_HELP,
        [this] (CMap &) {
            Healing();
            m_Direction = EDirection::LEFT;
            m_Stats.m_Points += 10;
            return true;
        }
    };
}

CGameCommand CPlayerHuman::MoveRightCommand() {
    return CGameCommand {
        MOVE_RIGHT_HELP,
        [this] (CMap &) {
            Healing();
            m_Direction = EDirection::RIGHT;
            m_Stats.m_Points += 10;
            return true;
        }
    };
}

CGameCommand CPlayerHuman::HelpCommand() const {
    return CGameCommand {
        PLAYER_HELP_COMMAND,
        [this] (CMap &) {
            m_Interface->PrintLineText (KNOWN_GAME_COMMANDS, EColors::CYAN);
            for (auto &command : m_Commands)
                command.second.GetHelp (m_Interface, command.first);
            m_Interface->PrintLine (EColors::CYAN);
            return false;
        }
    };
}

CGameCommand CPlayerHuman::PauseCommand() {
    return CGameCommand {
        PAUSE_HELP,
        [] (CMap &) {
            return false;
        }
    };
}

CGameCommand CPlayerHuman::JumpCommand() {
    return CGameCommand {
        JUMP_HELP,
        [this] (CMap & map) {
            Healing();
            CCoord under = GetCoord();
            under.getDown();
            if ( !map.canWalkTrough(under) ) {
                m_Direction = EDirection::UP;
                m_Stats.m_Points += 10;
                return true;
            }
            return false;
        }
    };
}

CGameCommand CPlayerHuman::HitDownCommand() {
    return CGameCommand {
        HIT_DOWN_HELP,
        [this] (CMap & map){
            if (m_Stats.m_Energy < 10)
                return false;
            CCoord coord (GetCoord());
            coord.getDown();
            HitBlock (map, coord);
            return true;
        }
    };
}

CGameCommand CPlayerHuman::HitLeftCommand() {
    return CGameCommand {
        HIT_LEFT_HELP,
        [this] (CMap & map){
            if (m_Stats.m_Energy < 10)
                return false;
            CCoord coord (GetCoord());
            coord.getLeft();
            HitBlock (map, coord);
            return true;
        }
    };
}

CGameCommand CPlayerHuman::HitRightCommand() {
    return CGameCommand {
        HIT_RIGHT_HELP,
        [this] (CMap & map){
            if (m_Stats.m_Energy < 10)
                return false;
            CCoord coord (GetCoord());
            coord.getRight();
            HitBlock (map, coord);
            return true;
        }
    };
}

CGameCommand CPlayerHuman::HitUpCommand() {
    return CGameCommand {
        HIT_UP_HELP,
        [this] (CMap & map){
            if (m_Stats.m_Energy < 10)
                return false;
            CCoord coord (GetCoord());
            coord.getUp();
            HitBlock (map, coord);
            return true;
        }
    };
}

CGameCommand CPlayerHuman::SwapWeapons() {
    return CGameCommand (
        SWAP_WEAPONS_HELP,
        [this] (CMap &){
            Healing();
            std::swap (m_InHand, m_Second);
            m_Direction = EDirection::NONE;
            return true;
        }
    );
}

CPlayer &CPlayerHuman::HitBlock( CMap & map, const CCoord & coord ) {
    map.GetField(coord).receiveHit(*m_InHand);
    if (map.GetField(coord).isDestroyed()){
        m_Stats.m_Points += 100;
        map.SetAir(coord);
    }
    Healing();
    m_Direction = EDirection::NONE;
    m_Stats.m_Energy -= 10;
    return *this;
}

CGameCommand CPlayerHuman::PlaceBlockCommand() {
    return CGameCommand {
        PLACE_BLOCK_HELP,
        [this] (CMap & map){
            CCoord tmp (m_Coord);
            if (! map.canWalkTrough(tmp.getDown()))
                return false;
            if ( map.canWalkTrough(tmp.getDown()))
                return false;

            Healing();
            m_Direction = EDirection::NONE;
            tmp.getUp();
            map.SetField (tmp, 'X', 200);
            m_Stats.m_Points += 10;
            return true;
        }
    };
}
