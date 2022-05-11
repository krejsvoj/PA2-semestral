/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <memory>
#include <fstream>
#include "CMap.h"
#include "CPlayer.h"
#include "CInterface.h"
#include "CCoord.h"
#include "CPlayerHuman.h"
#include "CPlayerMonster.h"
#include "EColors.h"
#include "EDirection.h"
#include "CBuffer.h"
#include "CMyExeptions.h"

/**
 * @brief
 * Class that represents the game
 *
 */

class CGame {
public:

    /**
     * Constructor CGame is made explicit because there is a single argument
     *
     * @param interface     (interface that communicates with user)
     */
    explicit CGame ( std::shared_ptr <CInterface> & interface );

    /**
     * Destructor is default because every variable can destroy itself
     *
     */
    ~CGame () = default;

    /**
     * Copy constructor is deleted. It is not desirable to copy the state of the game.
     *
     */
    CGame ( const CGame & ) = delete;

    /**
     * Operator = is deleted. It is not desirable to copy the state of the game.
     *
     */
    CGame & operator = ( const CGame & ) = delete;

    /**
     * Move operator =
     *
     * @param game          (game that has to be moved)
     * @return              (itself)
     */
    CGame & operator = ( CGame && game ) noexcept;

    /**
     * Method that initialize the game. Method is made noexcept because move constructor is used.
     * Method is not made const because it changes multiple variables.
     *
     * @param input       (input file from which the game should be initialized)
     * @return            (if initialization was successful)
     */
    bool Init ( std::fstream & input );

    /**
     * Method that makes one game tick.
     * Method is not made const because it changes multiple variables.
     *
     * @return            (true / false depending on which command was loaded (false for p - "pause"))
     */
    bool Tick ();

    /**
     * Method that redraws the state of the game to the console (map, players, stats)
     * Method is made const because it doesn't change anything, only prints the state of the game.
     *
     * @return          (true/false depending on player command)
     */
    void redrawConsole () const;

    /**
     * Method that saves the game to the filename.
     * Method is made const because it only saves data to a file.
     *
     * @param filename       (filename)
     * @return true          (if saving map was successful)
     */
    bool SaveGame ( const std::string & filename ) const;

private:

    /**
     * Method that represents the gravity. If the player is not jumping he will fall downwards.
     * The player can die by falling from a great height.
     * Method is not made const because it returns a non-const reference on itself.
     *
     * @throw       (YouDiedException - exception that says, that the player died by falling)
     * @throw       (KilledByMonster - exception that says, that the player fall on the monster and lost the combat)
     * @return      (itself)
     */
    CGame & Gravity ();

    /**
     * Method that checks whether players are not staying onto a block that deals damage.
     * Also removes players if they died.
     * Method is not made const because it returns a non-const reference on itself.
     *
     * @throw      (StepInLava - exception that says, that the user step in lava)
     * @return     (itself)
     */
    CGame & CheckCollisions ();

    /**
     * Asks player to take their turn. Human player can select from multiple commands.
     * Monster player moves in order to an AI.
     * Method is not made const because it changes the state of the game.
     *
     * @return      (true/false depending on which command was called)
     */
    bool TakeTurn ();

    /**
     * Method that moves players in order to their direction and if they can move on that
     * place on the map (some blocks does not allow to walk through).
     * Method is not made const because it returns a non-const reference on itself.
     *
     * @return      (itself)
     */
    CGame & MovePlayers ();

    /**
     * Method that represents a fight between two players. The fight lasts until one of the
     * players dies. It is randomly chosen which player starts.
     * Method is not made const because it returns a non-const reference on itself.
     *
     * @param first       (first player)
     * @param second      (second player)
     * @throw             (KilledByMonster - exception that says that the human player was killed by a monster)
     * @return            (itself)
     */
    CGame & TakeFight ( CPlayer & first, CPlayer & second );

    /**
     * Method that initializes the game map when InitGame is called. It checks whether
     * the map is correctly saved.
     * Method is not made const because it changes the game map.
     *
     * @param input       (file from which the game is being loaded)
     * @return            (if map was successfully loaded)
     */
    bool LoadMap ( std::fstream & input );

    /**
     * Method that initializes human player from a file. It checks whether the player is
     * correctly saved.
     * Method is not made const because it changes the m_Players variable.
     *
     * @param input       (file from which the player is being loaded)
     * @return true       (if player was correctly loaded)
     */
    bool LoadUser ( std::fstream & input );

    /**
     * Method that initializes monster player from a file. It checks whether the player is
     * correctly saved.
     * Method is not made const because it changes the m_Players (vector) variable.
     *
     * @param input       (file from which the player is being loaded)
     * @return            (if player was correctly loaded)
     */
    bool LoadMonster ( std::fstream & input );

    /**
     * Method that loads players from a file.
     * Method is not made const because it changes the m_Players (vector) variable.
     *
     * @param input     (file from which the player is being loaded)
     * @return          (if players are correctly loaded)
     */
    bool LoadPlayers ( std::fstream & input );

    /**
     * Static method that returns the direction in order to the loaded char.
     *
     * @param dir          (loaded direction as char)
     * @param direction    (direction to be set)
     * @return             (if direction is known and set)
     */
    static bool GetDirection ( char dir, EDirection & direction );

    /** Variable representing a map, where players are playing */
    std::unique_ptr <CMap> m_Map = nullptr;
    /** Variable that represent all the players playing the game */
    std::vector <std::unique_ptr<CPlayer>> m_Players = {};
    /** Auxiliary variable to print the game state */
    std::unique_ptr <CBuffer> m_Buffer = nullptr;
    std::shared_ptr <CInterface> m_Interface;

    static constexpr size_t MAX_MAP_WIDTH = 70;
    static constexpr size_t MIN_MAP_WIDTH = 20;
    static constexpr size_t MAX_MAP_HEIGHT = 30;
    static constexpr size_t MIN_MAP_HEIGHT = 10;
};