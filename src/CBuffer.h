/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 01.06.2021
 */

#pragma once

#include <memory>
#include <iostream>
#include <vector>
#include "CMap.h"
#include "CCoord.h"
#include "CStats.h"

/**
 * @brief
 * Auxiliary class class which is used to print the status of the game to the console
 *
 */
class CBuffer {

public:

    /**
     * Constructor CBuffer initializes the m_Map variable that represents the game maps.
     *
     * @param height    (height of the map)
     * @param width     (width of the map)
     */
    CBuffer ( size_t height, size_t width );

    /**
     * Method that prints the map into the buffer.
     * Method is not made const because it changes the whole buffer.
     *
     * @param map       (map that has to be printed into the buffer)
     */
    void DrawMapInBuffer ( CMap & map );

    /**
     * Method that prints char into specific place in the map. the location
     * is determined by coordinates.
     * Method is not made const because it changes the buffer.
     *
     * @param coord   (coordinate that determines the position)
     * @param c       (character to be printed)
     * @return        (itself)
     */
    CBuffer & PrintCharInMap ( const CCoord & coord, char c );

    /** Variable that represents a 2D map */
    std::vector <std::vector <char>> m_Map;

    /** Variable that represents CPlayerHuman statistics */
    CStats * m_Stats = nullptr;
    size_t m_MapHeight = 0;
    size_t m_MapWidth = 0;
};



