/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CFieldBorder.h"

using namespace std;

CFieldBorder::CFieldBorder(int HP)
        : CField (false, false, HP)
{
    if (m_HP <= 0)
        m_HP = 1;
}

CField &CFieldBorder::receiveHit(const CItem &item) {
    (void) item; // item is not used for CFieldBorder, because it has no meaning (cannot be destroyed)
    return * this;
}

int CFieldBorder::DealsDamage() const {
    return BORDER_DMG;
}

char CFieldBorder::DrawChar() const {
    return '#';
}

std::unique_ptr<CField> CFieldBorder::Clone() const {
    return std::make_unique <CFieldBorder> (*this);
}
