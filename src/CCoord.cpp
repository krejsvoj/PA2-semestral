/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CCoord.h"

using namespace std;

CCoord::CCoord(size_t x, size_t y)
        : m_X (x),
          m_Y (y)
{
}

CCoord &CCoord::operator=(CCoord rhs) {
    std::swap (m_X, rhs.m_X);
    std::swap (m_Y, rhs.m_Y);
    return *this;
}

CCoord::CCoord(const CCoord &rhs) {
    m_X = rhs.m_X;
    m_Y = rhs.m_Y;
}

CCoord &CCoord::getLeft() {
    m_Y--;
    return *this;
}


/**                 +y
 *      -------------->
 *      |   (  ,  ,  )
 *      |   (  ,  ,  )
 *      |   (  ,  ,  )
 *   +x v   (  ,  ,  )
 */

CCoord &CCoord::getRight() {
    m_Y++;
    return *this;
}

CCoord &CCoord::getDown() {
    m_X++;
    return *this;
}

CCoord &CCoord::getUp () {
    m_X--;
    return *this;
}

bool CCoord::operator == (const CCoord &rhs) const {
    return m_X == rhs.m_X && m_Y == rhs.m_Y;
}
