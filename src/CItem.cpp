/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CItem.h"

using namespace std;

CItem::CItem(std::string type)
        : m_Type ( std::move (type) ),
          m_Damage ( DEFAULT_ITEM_DMG ),
          m_Level ( DEFAULT_LEVEL )
{
}

std::string CItem::Type() const {
    return m_Type;
}

int CItem::Damage() const {
    return m_Damage * m_Level;
}

CItem &CItem::LevelUP() {
    m_Level++;
    return *this;
}

CItem::CItem(const CItem &item) {
    m_Type = item.m_Type;
    m_Damage = item.m_Damage;
    m_Level = item.m_Level;
}

CItem &CItem::operator=(CItem other) {
    std::swap (m_Type, other.m_Type);
    std::swap (m_Damage, other.m_Damage);
    std::swap (m_Level, other.m_Level);
    return *this;
}
