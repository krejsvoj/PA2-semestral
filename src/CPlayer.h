/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <memory>
#include <cstddef>
#include <iostream>
#include <fstream>
#include "CCoord.h"
#include "CMap.h"
#include "EDirection.h"
#include "CBuffer.h"
#include "CMyExeptions.h"

/**
 * @brief
 * This class is an abstract class representing a player.
 *
 */

class CPlayer {

public:

    /**
     * Constructor that initializes all the variables needed.
     *
     * @param hp             (player's HP)
     * @param coord          (player's coordinates)
     * @param airTime        (player's air time)
     * @param direction      (direction the player wants to move)
     * @param lastDirection  (the last player's direction)
     */
    CPlayer ( int hp, const CCoord & coord, size_t airTime, EDirection direction,
              EDirection lastDirection );

    /**
     * Copy constructor is deleted, because CPlayer is an abstract class.
     *
     */
    CPlayer ( const CPlayer & ) = delete;

    /**
     * Operator = is deleted because CPlayer is an abstract class.
     *
     */
    CPlayer & operator = ( const CPlayer & ) = delete;

    /**
     * Destructor is made virtual, because CPlayer is an abstract class.
     *
     */
    virtual ~CPlayer () = default;

    /**
     * Virtual method that represents one turn of the player. Turn is called every game
     * tick and every player can chose what to do.
     * Method is not made const because it changes player's stats.
     *
     * @param map        (the map according to which the player can make a decision)
     * @return           (true/false according to the selected command and success / failure on it)
     */
    virtual bool TakeTurn ( CMap & map ) = 0;

    /**
     * Virtual method that represents player being hit by a damage.
     * Method is not made const because it changes player stats.
     *
     * @param  damage     (amount of damage)
     * @return            (itself)
     */
    virtual CPlayer & ReceiveHit ( size_t damage ) = 0;

    /**
     * Virtual method that returns a char which belongs to the specific player.
     * Method is made const because it only returns a char.
     *
     * @return      (character how player is printed into buffer)
     */
    virtual char Print () const = 0;

    /**
     * Virtual method that represents how a player attacks.
     * Method is not made const because player can lose energy by attacking.
     *
     * @return      (amount of damage)
     */
    virtual size_t Attack () = 0;

    /**
     * Virtual method that prints a player into the buffer.
     * Method is not made const because player updates his stats before being printed.
     *
     * @param buffer      (buffer where the player has to be printed)
     */
    virtual void DrawIntoBuffer ( CBuffer & buffer ) = 0;

    /**
     * Virtual method that saves a player into the file.
     * Method is made const because it only prints the player into the file (does not change any variable)
     *
     * @param filename    (file where the player has to be saved)
     */
    virtual void SavePlayer ( std::ofstream & filename ) const = 0;

    /**
     * Virtual method that creates an unique_ptr to the specific inherited class. This method
     * allows to copy those objects.
     * Method is made const because it only creates a deep copy.
     *
     * @return      (unique_ptr to the object)
     */
    virtual std::unique_ptr <CPlayer> Clone () const = 0;

    /**
     * Method that returns player's coordinates.
     * Method is made const because it doesn't change any variable.
     *
     * @return      (player's coordinates)
     */
    const CCoord & GetCoord () const;

    /**
     * Moves player to the required coordinates.
     * Method is not made const because it changes player coordinates.
     *
     * @param coord     (coordinates to be moved to)
     * @return          (itself)
     */
    CPlayer & Move ( const CCoord & coord );

    /**
     * Method that returns coordinates where the player wants to move. It determines
     * these coordinates based on the player's direction
     * Method is not made const because it changes the variable m_LastDirection.
     *
     * @return      (coordinates where the player wants to move)
     */
    CCoord coordToMove ();

    /**
     * Method that returns whether the player is alive.
     * Method is made const because it only returns true/false (does not change any variable)
     *
     * @return     (if the player is alive)
     */
    bool isAlive () const;

    /**
     * Method that increments player's time in air. If reset variable is set to true, it
     * reset the air time to 0.
     * Method is not made const because it changes the m_AirTime variable.
     *
     * @param reset        (whether the air time counter should be reset)
     */
    void TimeInAir ( bool reset );

    /**
     * Method that returns player's time in air.
     * Method is made const because it only returns value of air time.
     *
     * @return     (player's time in air)
     */
    size_t GetTimeInAir () const;

    /**
     * Method that resets player direction (sets his direction to EDirection::NONE)
     * Method is not made const because it changes CPlayer variables.
     *
     * @return    (itself)
     */
    CPlayer & resetDirection ();

    /**
     * Method that returns player's last direction.
     * Method is made const because it only returns a value.
     *
     * @return    (player's last direction)
     */
    EDirection getLastDirection () const;

protected:

    /**
     * Static method that return's a character based on the direction. It is used to save players.
     *
     * @param direction      (the direction)
     * @return               (character based on the direction)
     */
    static char CharDirection ( EDirection direction );

    int m_HP = 100;
    CCoord m_Coord;
    size_t m_TimeInAir = 0;
    EDirection m_Direction;
    EDirection m_LastDirection;
};