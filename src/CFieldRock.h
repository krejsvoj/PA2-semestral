/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 03.06.2021
 */

#pragma once

#include "CField.h"

/**
 * @brief
 * Class that represents a specific field: ROCK
 *
 */

class CFieldRock : public CField {
public:

    /**
     * Constructor CFieldRock is made explicit because it has only one argument
     * If HP (as param[in] is > ROCK_MAX_HP (constant) m_HP is set to this constant
     *
     * @param       (HP of the block)
     */
    explicit CFieldRock ( int HP );

    /**
     * Overridden method that decreases block HP. If the block is hit by an item of type "Pickaxe"
     * the damage is multiplied. The block can be destroyed by being hit.
     *
     * @param item        (item that hits the block)
     * @return            (itself)
     */
    CField & receiveHit ( const CItem & item ) override;

    /**
     * Method that returns how much damage the block deals.
     *
     * @return       (amount of damage)
     */
    int DealsDamage () const override;

    /**
     * Method that returns a char that can be printed later.
     *
     * @return      (character - rock is represented as char 'C' or 'c' depending on its HP)
     */
    char DrawChar () const override;

    /**
     * Method that makes copy of itself and returns it as an unique_ptr.
     *
     * @return      (pointer to the copied object)
     */
    std::unique_ptr <CField> Clone () const override;

private:
    static constexpr int ROCK_MAX_HP = 500;
    static constexpr int ROCK_DMG = 0;
};



