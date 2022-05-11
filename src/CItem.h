/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <string>

/**
 * @brief
 * Class that represents items that an user can use
 *
 */

class CItem {
public:

    /**
     * Constructor CItem is made explicit because it has only one argument
     *
     * @param type      (type of item)
     */
    explicit CItem ( std::string type );

    /**
     * Destructor is made default because every variable can destroy itself.
     *
     */
    ~CItem () = default;

    /**
     * Copy constructor that simply copies every member variable.
     *
     * @param item    (item to by copied)
     */
    CItem ( const CItem & item );

    /**
     * Simple operator = . Copy & swap method is used.
     *
     * @param other
     * @return          (itself)
     */
    CItem & operator = ( CItem other );

    /**
     * Method that returns which type the item is.
     * Method is made const because it only returns a value.
     *
     * @return     (item type)
     */
    std::string Type () const;

    /**
     * Method that returns how much damage the item does.
     * Method is made const because it only returns a value.
     *
     * @return    (amount of damage)
     */
    int Damage () const;

    /**
     * Method that levels up the item.
     * Method is not made const because it changes variable and returns non-const reference on itself.
     *
     * @return    (itself)
     */
    CItem & LevelUP ();

private:
    static constexpr int DEFAULT_LEVEL = 1;
    static constexpr int DEFAULT_ITEM_DMG = 5;
    std::string m_Type;
    int m_Damage;
    int m_Level;
};