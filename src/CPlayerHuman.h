/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 05.05.2021
 */

#pragma once

#include <memory>
#include <map>
#include "CPlayer.h"
#include "CItem.h"
#include "CCoord.h"
#include "CInterface.h"
#include "CStats.h"
#include "CMap.h"
#include "CGameCommand.h"
#include "messages.h"

/**
 * @brief
 * Class that represents special type of a player: HUMAN (user)
 *
 */

class CPlayerHuman : public CPlayer {
public:

    /**
     * Constructor that initializes every variable of CPlayerHuman. There are also
     * created commands for the human player int his constructor.
     *
     * @param coord             (player's coordinates)
     * @param stats             (player's stats)
     * @param airTime           (player's time in air)
     * @param interface         (interface to communicate between the user and the interface)
     * @param direction         (player's direction)
     * @param lastDirection     (player's last direction)
     */
    CPlayerHuman ( const CCoord & coord, CStats & stats, size_t airTime, std::shared_ptr <CInterface> & interface,
                   EDirection direction, EDirection lastDirection );

    /**
     * Copy constructor of CPlayerHuman. A deep copy is made.
     *
     * @param other      (human player to be copied)
     */
    CPlayerHuman ( const CPlayerHuman & other );

    /**
     * Operator =. Copy & swap method is used.
     *
     * @param other    (human player to be copied)
     * @return         (itself)
     */
    CPlayerHuman & operator = ( CPlayerHuman other );

    /**
     * Method that saves a human player to a file.
     *
     * @param filename     (file where the player has to be saved)
     */
    void SavePlayer ( std::ofstream & filename ) const override;

    /**
     * Method that represents player being hit by some damage. The damage is decreased by
     * player's armor.
     *
     * @param damage     (amount of damage)
     * @return           (itself)
     */
    CPlayer & ReceiveHit ( size_t damage ) override;

    /**
     * Method that represents player's attack. Player's attack can be stronger if he has
     * enough energy.
     *
     * @throw       (YouDiedException - if the player died)
     * @return      (amount of damage)
     */
    size_t Attack () override;

    /**
     * Method that returns a character of the player to be printed in the buffer. The character
     * is chosen in order to the player's last direction.
     *
     * @return     (character)
     */
    char Print () const override;

    /**
     * Method that represents CPlayerHuman's turn. The player has multiple choices what to do.
     * There are some command from whose he can chose.
     *
     * @param map    (a map according to which he can make decisions)
     * @return       (true if any command except "p" (pause) command is chosen)
     */
    bool TakeTurn ( CMap & map ) override;

    /**
     * Method that represents player being printed into the buffer.
     *
     * @param buffer      (buffer to be printed in)
     */
    void DrawIntoBuffer ( CBuffer & buffer ) override;

    /**
     * Method that is used by HitCommands and represents player hitting objects in the map.
     * Method is not made const because it changes player stats (m_Points)
     *
     * @param map        (map where the object are being hit)
     * @param coord      (coordinates of the block that should be hit)
     * @return           (itself)
     */
    CPlayer & HitBlock ( CMap & map, const CCoord & coord );

    /**
     * Method that makes copy of itself and returns it as an unique_ptr.
     *
     * @return      (pointer to the copied object)
     */
    std::unique_ptr<CPlayer> Clone () const override;

private:

    /** Game command which swaps player's weapons. */
    CGameCommand SwapWeapons ();

    /** Game command which sets players direction to the left */
    CGameCommand MoveLeftCommand ();

    /** Game command which sets players direction to the right */
    CGameCommand MoveRightCommand ();

    /** Game command which sets players direction as "up" */
    CGameCommand JumpCommand ();

    /** Game command which prints help for each command */
    CGameCommand HelpCommand () const;

    /** Game command which hits the block under the player */
    CGameCommand HitDownCommand ();

    /** Game command which hits the block on the left of the player */
    CGameCommand HitLeftCommand ();

    /** Game command which hits the block on the right of the player */
    CGameCommand HitRightCommand ();

    /** Game command which hits the block above the player */
    CGameCommand HitUpCommand ();

    /** Game command that places a block under the player */
    CGameCommand PlaceBlockCommand ();

    /** Game command which return from game mode to the application menu */
    static CGameCommand PauseCommand () ;

    /**
     * Method which updates player's stats.
     * Method is not made const because it changes player's stats.
     *
     * @return      (reference to player's stats)
     */
    CStats & UpdateStats ();

    /**
     * Method that represents player's healing. Player is being healed every game tick.
     * Recovers energy and HP.
     * Method is not made const because it changes player's stats.
     *
     * @return      (itself)
     */
    CPlayerHuman & Healing ();

    /**
     * Method that levels up the player
     * Method is not made const because it changes player's stats.
     *
     * @return     (itself)
     */
    CPlayer & LevelUP ();

    CStats m_Stats;
    std::shared_ptr <CInterface> m_Interface;
    std::unique_ptr <CItem> m_InHand;
    std::unique_ptr <CItem> m_Second;
    std::map <std::string, CGameCommand> m_Commands = {};
    std::set <std::string> m_KnownCommands = {};
    static constexpr int MAX_ENERGY = 100;
    static constexpr int HUMAN_MAX_HP = 100;
};