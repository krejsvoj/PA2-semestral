/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CField.h"

using namespace std;

CField::CField(bool walkThrough, bool isDestroyed, int HP)
        : m_HP (HP),
        m_WalkThrough (walkThrough),
        m_isDestroyed (isDestroyed)
{
}

bool CField::canWalkThrough() const {
    return m_WalkThrough;
}

bool CField::isDestroyed() const {
    return m_isDestroyed;
}

void CField::SaveField(ofstream &mapFile, size_t coordX, size_t coordY) const {
    char FieldChar = (char) toupper(DrawChar());
    mapFile << FieldChar << " " << coordX << " " << coordY << " " << m_HP << std::endl;
}
