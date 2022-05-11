/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <algorithm>

/**
 * @brief
 * CCoord is a class representing coordinates. The coordinates are arranged as in a matrix.
 * X is up/down axis (increasing X is shifting down in the matrix)
 * Y is left/right axis (increasing Y is shifting right in the matrix)
 *
 */
class CCoord {
public:

    /**
     * Constructor that initializes the coordinates
     * @param x     (x-coordinate)
     * @param y     (y-coordinate)
     *
     */
    CCoord ( size_t x, size_t y );

    /**
     * Assignment operator = that assigns specific coordinates. Copy & swap method is used.
     *
     * @param rhs        (coordinate that has to be assigned)
     * @return           (assigned coordinate)
     */
    CCoord & operator = ( CCoord rhs );

    /**
     * Copying constructor. Makes a deep copy
     *
     * @param rhs        (coordinate that has to be copied)
     */
    CCoord ( const CCoord & rhs );

    /**
     * Destructor. The destructor is set to default, because none class variable is dynamically
     * allocated.
     *
     */
    ~CCoord () = default;

    /**
     * Method which shifts the coordinates one place to the left.
     * Method is not made const because it changes its variables.
     *
     * @return         (itself)
     */
    CCoord & getLeft ();

    /**
     * Method which shifts the coordinates one place to the right.
     * Method is not made const because it changes its variables.
     *
     * @return        (itself)
     */
    CCoord & getRight ();

    /**
     * Method which shifts the coordinates one place down.
     * Method is not made const because it changes its variables.
     *
     * @return        (itself)
     */
    CCoord & getDown ();

    /**
     * Method which shifts the coordinates one place up.
     * Method is not made const because it changes its variables.
     *
     * @return        (itself)
     */
    CCoord & getUp ();

    /**
     * Method that checks whether two coordinates are the same. Compares individual variables.
     * Method is made const because it only returns true / false value (does not change any variable)
     *
     * @param rhs    (coordinate against which the coordinate should be compared)
     * @return       (if coordinates are equal)
     */
    bool operator == ( const CCoord & rhs ) const;

    size_t m_X;
    size_t m_Y;
};