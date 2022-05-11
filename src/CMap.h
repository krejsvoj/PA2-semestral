/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include <fstream>
#include "CField.h"
#include "CCoord.h"
#include "CFieldClay.h"
#include "CFieldBorder.h"
#include "CFieldAir.h"
#include "CFieldLava.h"
#include "CFieldRock.h"
#include "messages.h"

/**
 * @brief
 * Class that represents a map of CFields. (2D vector)
 *
 */

class CMap {
public:

    /**
     * Constructor that initializes map based on the input height and width
     *
     * @param height    (map height)
     * @param width     (map width)
     */
    CMap ( size_t height, size_t width );

    /**
     * Copy constructor that makes a deep copy.
     *
     * @param map      (map to be copied)
     */
    CMap ( const CMap & map );

    /**
     * Operator = that uses copy & swap method.
     *
     * @param map      (map to be copied)
     * @return
     */
    CMap & operator = ( CMap map );

    /**
     * Destructor is set as default because every member variable can destroy itself
     *
     */
    ~CMap () = default;

    /**
     * Method that returns whether it is possible to walk through the object selected by
     * coordinates.
     * Method is made const because it only returns true / false value (doesn't change anything)
     *
     * @param coord      (coords of selected object)
     * @return           (if it is possible to walk through the object at the given coordinates)
     */
    bool canWalkTrough ( const CCoord & coord ) const;

    /**
     * Method that returns an CField at the given coordinates.
     *
     * @param coord     (coords of selected object)
     * @throw           (runtime_error - if the coordinates are out of the map)
     * @return          (return reference to an object at the given coordinates)
     */
    CField & GetField ( const CCoord & coord ) const;

    /**
     * Method that sets CFieldAir at the given coordinates.
     * Method is not made const because it changes m_Map variable.
     *
     * @param coord      (given coordinates)
     * @throw            (runtime_error - if the coordinates are out of the map or the map is not initialized)
     * @return           (itself)
     */
    CMap & SetAir ( const CCoord & coord );

    /**
     * Method that sets a specific field at the given coordinates.
     * Method is not made const because it changes the variable m_Map.
     *
     * @param coord    (given coordinates)
     * @param c        (character that represents specific field)
     * @param HP       (HP to initialize object HP)
     * @throw          (runtime_error - if the coordinates are out of the map)
     * @return         (if setting the field was successful)
     */
    bool SetField ( const CCoord & coord, char c, int HP );

    /**
     * Method that checks whether the object at the given position might be border.
     * Method is made const because it only returns true / false (does not change anything)
     *
     * @param x      (x - coordinate)
     * @param y      (y - coordinate)
     * @return       (if at the given position might be border)
     */
    bool isBorder (size_t x, size_t y ) const;

    /**
     * Method that checks whether the given coordinates are in the map (if they are not
     * out of index)
     * Method is made const because it only returns true/false (does not change any variable)
     *
     * @param coord      (given coordinates)
     * @return           (if it is inside of the map)
     */
    bool isInside ( const CCoord & coord ) const;

    /**
     * Method that saves the map to the given output stream in specific format.
     * Method is made const because it only save the map (does not change it)
     *
     * @param mapFile    (map file)
     */
    void SaveMap ( std::ofstream & mapFile ) const;

private:
    size_t m_Height;
    size_t m_Width;
    std::vector <std::vector <std::unique_ptr<CField>>> m_Map = {};
};