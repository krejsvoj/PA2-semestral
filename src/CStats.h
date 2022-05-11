/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 28.05.2021
 */

#pragma once

/**
 * Auxiliary class that represents stats of the player
 *
 */

struct CStats {

    int m_Energy = 100;
    int m_HP = 100;
    int m_Armor = 10;
    size_t m_Level = 1;
    int m_ItemDamage = 0;
    int m_SecondItemDamage = 0;
    size_t m_Points = 0;
    std::string m_ItemName;
    std::string m_SecondItemName;

};
