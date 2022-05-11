/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CPlayer.h"

using namespace std;

CPlayer::CPlayer(int hp, const CCoord &coord, size_t airTime, EDirection direction, EDirection lastDirection)
        : m_HP(hp),
        m_Coord(coord),
        m_TimeInAir(airTime),
        m_Direction (direction),
        m_LastDirection (lastDirection)
{
}

const CCoord &CPlayer::GetCoord() const {
    return m_Coord;
}

CPlayer &CPlayer::Move(const CCoord &coord) {
    m_Coord.m_X = coord.m_X;
    m_Coord.m_Y = coord.m_Y;
    return * this;
}

CCoord CPlayer::coordToMove() {
    m_LastDirection = m_Direction;

    switch (m_Direction){
        case EDirection::NONE:  return m_Coord;
        case EDirection::LEFT:  return CCoord ( m_Coord.m_X, m_Coord.m_Y  - 1 );
        case EDirection::RIGHT: return CCoord ( m_Coord.m_X, m_Coord.m_Y  + 1 );
        case EDirection::UP:    return CCoord ( m_Coord.m_X - 1, m_Coord.m_Y);
    }
    return m_Coord;
}

bool CPlayer::isAlive() const {
    return m_HP >= 0;
}

void CPlayer::TimeInAir (bool reset) {
    if ( reset )
        m_TimeInAir = 0;
    else m_TimeInAir++;
}

size_t CPlayer::GetTimeInAir() const {
    return m_TimeInAir;
}

EDirection CPlayer::getLastDirection() const{
    return m_LastDirection;
}

CPlayer &CPlayer::resetDirection() {
    m_Direction = EDirection::NONE;
    return * this;
}

char CPlayer::CharDirection(EDirection direction) {
    switch (direction){
        case EDirection::UP:    return 'U';
        case EDirection::NONE:  return 'N';
        case EDirection::RIGHT: return 'R';
        case EDirection::LEFT:  return 'L';
    }
    return 'N';
}
