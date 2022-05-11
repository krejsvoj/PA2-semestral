/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include "CField.h"
#include "CItem.h"
#include <iostream>

/**
 * @brief
 * Class that represents a specific field: LAVA
 *
 */

class CFieldLava : public CField{
public:

    /**
     * Constructor CFieldLava is made explicit because it has only one argument
     *
     * @param       (HP of the block)
     */
    explicit CFieldLava ( int HP );

    /**
     * Overridden method that might decrease block HP, but lava cannot be destroyed by items,
     * so nothing happens when lava is hit.
     *
     * @param item        (item that may hit the block)
     * @return            (itself)
     */
    CField & receiveHit ( const CItem &item ) override;

    /**
     * Method that returns how much damage the block deals.
     *
     * @return       (amount of damage - LAVA_DMG constant)
     */
    int DealsDamage () const override;

    /**
     * Method that returns a char that can be printed later.
     *
     * @return      (character - Lava is represented as char 'L')
     */
    char DrawChar () const override;

    /**
     * Method that makes copy of itself and returns it as an unique_ptr.
     *
     * @return     (pointer to the copied object)
     */
    std::unique_ptr <CField> Clone () const override;

private:
    static constexpr int LAVA_DMG = 1000;
};