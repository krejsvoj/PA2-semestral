/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CPlayerMonster.h"

using namespace std;


CPlayerMonster::CPlayerMonster(const CCoord &coord, int HP, size_t airTime, EDirection direction,
                               EDirection lastDirection, size_t damage, size_t count)
        : CPlayer(HP, coord, airTime, direction, lastDirection),
          m_Count(count),
          m_Damage(damage)
{
    if (m_Damage > MONSTER_MAX_DMG)
        m_Damage = MONSTER_MAX_DMG;
    if (m_HP > MONSTER_MAX_HP)
        m_HP = MONSTER_MAX_HP;
}

CPlayerMonster::CPlayerMonster(const CPlayerMonster &other)
        : CPlayer(other.m_HP, other.m_Coord, other.m_TimeInAir, other.m_Direction, other.m_LastDirection)
{
    m_Count = other.m_Count;
    m_Damage = other.m_Damage;
}

CPlayerMonster &CPlayerMonster::operator=(CPlayerMonster other) {
    std::swap (m_Count, other.m_Count);
    std::swap (m_Damage, other.m_Damage);
    std::swap (m_HP, other.m_HP);
    std::swap (m_Coord, other.m_Coord);
    std::swap (m_TimeInAir, other.m_TimeInAir);
    std::swap (m_Direction, other.m_Direction);
    std::swap (m_LastDirection, other.m_LastDirection);
    return *this;
}

CPlayer &CPlayerMonster::setMove(CMap & map) {
    CCoord tmpCoord = m_Coord;

    if (m_Count < 5) {
        tmpCoord.getLeft();
        if ( map.GetField(tmpCoord).DealsDamage() == 0 && map.canWalkTrough(tmpCoord) &&
        map.GetField(tmpCoord.getDown()).DealsDamage() == 0 && !map.canWalkTrough(tmpCoord) )
            m_Direction = EDirection::LEFT;
        else {
            m_Count = 5;
            m_Direction = EDirection::NONE;
        }
    }
    else if (m_Count > 5 && m_Count < 11) {
        tmpCoord.getRight();
        if ( map.GetField(tmpCoord).DealsDamage() == 0 && map.canWalkTrough(tmpCoord) &&
        map.GetField(tmpCoord.getDown()).DealsDamage() == 0 && !map.canWalkTrough(tmpCoord) )
            m_Direction = EDirection::RIGHT;
        else {
            m_Count = 0;
            m_Direction = EDirection::NONE;
        }
    }
    else m_Direction = EDirection::NONE;

    m_Count++;
    if (m_Count > 11)
        m_Count = 0;

    return *this;
}

size_t CPlayerMonster::Attack() {
    return (rand() % 5) + m_Damage;
}

CPlayer &CPlayerMonster::ReceiveHit(size_t damage) {
    m_HP -= (int) damage;
    return * this;
}

char CPlayerMonster::Print() const {
    if (m_Count > 5)
        return '}';
    else
        return '{';
}

bool CPlayerMonster::TakeTurn(CMap &map) {
    setMove(map);
    return true;
}

void CPlayerMonster::DrawIntoBuffer(CBuffer &buffer) {
    buffer.PrintCharInMap(m_Coord, Print());
}

std::unique_ptr<CPlayer> CPlayerMonster::Clone() const {
    return std::make_unique <CPlayerMonster> (*this);
}

void CPlayerMonster::SavePlayer(ofstream &filename) const {
    filename << PLAYER_MONSTER << std::endl;
    filename << m_Coord.m_X << " " << m_Coord.m_Y << std::endl;
    filename << m_HP << " " << m_TimeInAir << " " << m_Count << " " << m_Damage;
    filename << " " << CharDirection(m_Direction) << " " << CharDirection (m_LastDirection) << std::endl;
}
