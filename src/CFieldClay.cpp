/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CFieldClay.h"

using namespace std;

CFieldClay::CFieldClay(int HP)
        : CField ( false, false, HP)
{
    if (m_HP > CLAY_MAX_HP)
        m_HP = CLAY_MAX_HP;
}

CField &CFieldClay::receiveHit(const CItem &item) {
    int damage = item.Damage();
    if (item.Type() == PICKAXE)
        damage *= 10;

    m_HP -= damage;
    if (m_HP <= 0)
        m_isDestroyed = true;

    return * this;
}

int CFieldClay::DealsDamage() const {
    return CLAY_DMG;
}

char CFieldClay::DrawChar() const {
    if (m_HP <= CLAY_MAX_HP / 2)
        return 'x';
    return 'X';
}

std::unique_ptr<CField> CFieldClay::Clone() const {
    return std::make_unique <CFieldClay> (*this);
}
