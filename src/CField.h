/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <string>
#include <fstream>
#include <memory>
#include "CItem.h"
#include "messages.h"

/**
 * @brief
 * Abstract class that represents a field in a map
 *
 */

class CField {
public:

    /**
     * Constructor CField that initializes CField variables.
     *
     * @param walkThrough      (info whether it is possible to walk through the block)
     * @param isDestroyed      (info whether the block is destroyed or not)
     * @param HP               (HP that the block might have)
     */
    CField ( bool walkThrough, bool isDestroyed, int HP );

    /**
     * Destructor is made virtual because several classes inherit from this class
     *
     */
    virtual ~CField () = default;

    /**
     * Virtual method that represents block being hit by an item.
     * Method is not made const because variable m_HP is changed during this method.
     *
     * @param item    (item with which the block is being hit)
     * @return        (itself)
     */
    virtual CField & receiveHit ( const CItem &item ) = 0;

    /**
     * Virtual method that represents how much damage the block is dealing.
     * Method is made const because it only returns a value.
     *
     * @return      (amount of damage)
     */
    virtual int DealsDamage () const = 0;

    /**
     * Virtual method that return a char which has to be printed. The char represents the
     * specific class.
     * Method is made const because it only returns a character.
     *
     * @return      (character)
     */
    virtual char DrawChar () const = 0;

    /**
     * Virtual method that creates an unique_ptr to the specific inherited class. This method
     * allows to copy those objects.
     * Method is made const because it only makes a copy, doesn't change anything in the object.
     *
     * @return      (unique_ptr to the object)
     */
    virtual std::unique_ptr <CField> Clone () const = 0;

    /**
     * Method that decides whether it is possible to walk through the block or not.
     * Method is made const because it only returns true / false value.
     *
     * @return      (if can walk through)
     */
    bool canWalkThrough () const;

    /**
     * Method that decides whether the block is destroyed or not.
     * Method is made const because it only returns true / false value.
     *
     * @return      (if block is destroyed)
     */
    bool isDestroyed () const;

    /**
     * Method that saves the block to a file in a specific format.
     * Method is made const because it doesn't change any variable, only prints data into the file.
     *
     * @param mapFile        (file to which the block has to be saved)
     * @param coordX         (coordinate X)
     * @param coordY         (coordinate Y)
     */
    void SaveField ( std::ofstream & mapFile, size_t coordX, size_t coordY ) const;

protected:
    int m_HP;
    bool m_WalkThrough;
    bool m_isDestroyed;
};