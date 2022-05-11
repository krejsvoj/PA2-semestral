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
 * Class that represents a specific field: BORDER
 *
 */

class CFieldBorder : public CField {
public:

    /**
     * Constructor CFieldBorder is made explicit because it has only one argument
     *
     * @param      (HP of the block)
     */
    explicit CFieldBorder ( int HP );

    /**
     * Overridden method that might decrease block HP, but the border block cannot be destroyed.
     * It is used as the map border. Hitting this object cannot destroy him.
     *
     * @param item        (item that may hit the block)
     * @return            (itself)
     */
    CField & receiveHit ( const CItem &item ) override;

    /**
     * Method that returns how much damage the block deals.
     *
     * @return      (amount of damage)
     */
    int DealsDamage () const override;

    /**
     * Method that returns a char that can be printed later.
     *
     * @return      (character - border is represented as char '#')
     */
    char DrawChar () const override;

    /**
     * Method that makes copy of itself and returns it as an unique_ptr.
     *
     * @return      (pointer to the copied object)
     */
    std::unique_ptr <CField> Clone () const override;

private:
    static constexpr int BORDER_DMG = 0;
};



