/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 03.06.2021
 */

#include "CFieldRock.h"

CFieldRock::CFieldRock(int HP)
    : CField (false, false, HP)
{
    if (m_HP > ROCK_MAX_HP)
        m_HP = ROCK_MAX_HP;
}

CField &CFieldRock::receiveHit(const CItem &item) {
    int damage = item.Damage();
    if (item.Type() == PICKAXE)
        damage *= 10;

    m_HP -= damage;
    if (m_HP <= 0)
        m_isDestroyed = true;

    return *this;
}

int CFieldRock::DealsDamage() const {
    return ROCK_DMG;
}

char CFieldRock::DrawChar() const {
    if (m_HP <= ROCK_MAX_HP / 2)
        return 'c';
    return 'C';
}

std::unique_ptr<CField> CFieldRock::Clone() const {
    return std::make_unique <CFieldRock> (*this);
}
