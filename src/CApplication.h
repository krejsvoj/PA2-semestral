/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <string>
#include <map>
#include <memory>
#include "CCommand.h"
#include "CInterface.h"
#include "CGame.h"
#include "EColors.h"
#include "CMyExeptions.h"
#include "messages.h"

/**
 * @brief
 * The application is a class that runs the game. It is above the game
 * and allows the user to interact with the game.
 *
 */

class CApplication {
public:

    /**
     * Constructor of CApplication. It is marked as explicit, because only one argument is used.
     *
     * @param interface     (interface that allows communication between the user and the application)
     */
    explicit CApplication ( std::shared_ptr <CInterface> interface );

    /**
     * Copy constructor is deleted because it is not desirable to copy the state of the application.
     *
     */
    CApplication ( const CApplication & ) = delete;

    /**
     * Operator = is deleted as well for the same reason as copy constructor is deleted.
     *
     */
    CApplication & operator = ( const CApplication & ) = delete;

    /**
     * Destructor is marked as default because STL containers are used (they can destroy themselves)
     *
     */
    ~CApplication() = default;

    /**
     * Method that makes run the application. Infinite loop is used. User is being asked which
     * action he wants to take (there are several commands). Each command performs a specific
     * activity with a game or application.
     * Method is not made const because it changes the m_MapLoaded variable.
     *
     * @return      (number - 0 if "exit" command is used, 1 else)
     */
    int Run ();

private:

    /**
     * Method that initialize the game. The game is initialized from a file.
     * Method is not made const because it changes multiple variables (initializes the whole game)
     *
     * @param game      (game that has to be initialized)
     * @param input     (file from which the game has to be initialized)
     * @return          (true / false if initialization was successful)
     */
    bool InitGame ( CGame & game, std::fstream & input );

    /**
     * Method that created a PlayCommand. The command is initialized using the lambda function.
     *
     * @return         (PlayCommand (one of game commands that can be used))
     */
    CCommand PlayCommand ();

    /**
     * Method that created a NewGameCommand. The command is initialized using the lambda function.
     *
     * @return        (NewGameCommand is a command that initializes a new game)
     */
    CCommand NewGameCommand ();

    /**
     * Method that created a HelpCommand. The command is initialized using the lambda function.
     *
     * @return        (HelpCommand is a command that prints help for every command that can be used)
     */
    CCommand HelpCommand () const;

    /**
     * Method that created a LoadGameCommand. The command is initialized using the lambda function.
     *
     * @return        (LoadGame command is a command that loads game from a file (asks user for filename)
     */
    CCommand LoadGameCommand ();

    /**
     * Method that created a SaveCommand. The command is initialized using the lambda function.
     *
     * @return        (SaveGame command is a command that saves game to a filename (asks user for filename)
     */
    CCommand SaveCommand ();

    /**
     * Method that created an ExitCommand. The command is initialized using the lambda function.
     *
     * @return        (ExitCommand is a command that quits the game and the application)
     */
    static CCommand ExitCommand ();

    CCommand InfoCommand ();

    /**
     * Method that asks player whether he wants to play again. This method is called when the game
     * ended - the player died.
     * Method is not made const because it changes the variable m_MapLoaded.
     *
     * @param what   (message what happened)
     * @param game   (reference to the game that ended - to redraw it)
     * @return       (true / false if player wants to play again)
     */
    bool PlayAgain ( const std::string & what, CGame & game );

    bool m_MapLoaded = false;

    /** Game commands that can be used */
    std::map<std::string, CCommand> m_Commands = {};
    std::shared_ptr <CInterface> m_Interface;
    /** Game commands that are known and are passed for interface to load command */
    std::set<std::string> m_KnownCommands = {};
};