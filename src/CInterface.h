/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 02.05.2021
 */

#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <set>
#include <algorithm>
#include <fstream>
#include "CStats.h"
#include "EColors.h"
#include "CBuffer.h"
#include "messages.h"

/**
 * @brief
 * Class that represents an interface to communicate between the program and the user.
 * Methods are not made const because they return non-const reference on themself.
 *
 */

class CInterface {

public:

    /**
     * Constructor CInterface that initializes the ostream and istream
     *
     * @param in      (input stream)
     * @param out     (output stream)
     */
    CInterface ( std:: istream & in, std::ostream & out );

    /**
     * Destructor is made default because every class variable can destroy itself.
     *
     */
    ~CInterface () = default;

    /**
     * Operator = is deleted. It is not desirable to copy the state of the game.
     *
     */
    CInterface & operator = ( CInterface interface ) = delete;

    /**
     * Copy constructor is deleted. It is not desirable to copy the state of the game.
     *
     */
    CInterface ( const CInterface & interface ) = delete;

    /**
     * Method that clears the input.
     *
     * @return    (itself)
     */
    CInterface & ClearInput ();

    /**
     * Method that clears console
     *
     * @return    (itself)
     */
    CInterface & ClearConsole ();

    /**
     * Method that loads command from input stream
     *
     * @param command      (command that is loaded)
     * @return             (itself)
     */
    CInterface & loadCommand ( std::string & command );

    /**
     * Method that prints message in color.
     *
     * @param message      (message to be printed)
     * @param color        (color of the message)
     * @return             (itself)
     */
    CInterface & PromptMessage ( const std::string &message, EColors color );

    /**
     * Method that prints help message for commands.
     *
     * @param help           (command to which the help belows)
     * @param helpMessage    (help message)
     * @return               (itself)
     */
    CInterface & PromptHelpMessage ( const std::string & help, const std::string & helpMessage );

    /**
     * Method that prints that the file is corrupted.
     *
     * @return      (itself)
     */
    CInterface & PromptFileCorrupted ();

    /**
     * Method that prints main menu.
     *
     * @param color     (color of the menu)
     * @return          (itself)
     */
    CInterface & PrintMenu ( EColors color );

    /**
     * Method that prints player's stats
     *
     * @param stats     (stats to be printed)
     * @return          (itself)
     */
    CInterface & PrintStats ( const CStats & stats );

    CInterface & PrintInfo ();

    /**
     * Method that prints a text in the middle of a line.
     *
     * @param message    (message to be printed)
     * @param color      (color of the message)
     * @return           (itself)
     */
    CInterface & PrintLineText ( const std::string & message, EColors color );

    /**
     * Method that prints a line in chosen color.
     *
     * @param color    (color of the line)
     * @return         (itself)
     */
    CInterface & PrintLine ( EColors color );

    /**
     * Method that prints the buffer. Buffer contains data about actual state of the game.
     *
     * @param buffer    (buffer to be printed)
     * @return          (itself)
     */
    CInterface & PrintBuffer ( CBuffer & buffer );

    /**
     * Method that asks user for filename.
     *
     * @param input         (input stream)
     * @return              (if the file exists and can be loaded)
     */
    bool PromptLoadFilename ( std::fstream & input );

    /**
     * Method that asks user to chose which map he wants to play.
     *
     * @param input   (input stream)
     * @return        (if the map exists)
     */
    bool SelectMap ( std::fstream & input );

    /**
     * Method that checks whether the file doesn't exist yet.
     *
     * @param filename      (file name)
     * @return              (if map can be saved in this filename)
     */
    bool PromptSaveFile ( std::string & filename );

    /**
     * Method that asks player whether he wants to play again.
     *
     * @param what   (message what happened)
     * @return       (if player wants to play again)
     */
    bool PlayAgain ( const std::string & what );

    /**
     * Method that asks player for a command. It checks whether the command is known.
     *
     * @param knownCommands      (known commands)
     * @return                   (loaded command)
     */
    std::string GetCommand ( const std::set<std::string> &knownCommands );

private:

    /**
     * Method that converts string to lowercase.
     *
     * @param command  (command to be transformed)
     * @return         (itself)
     */
    CInterface & StringToLower ( std::string & command );

    /**
     * Method that prints char into the console. Every char has some special ansi escape code.
     *
     * @param c    (char to be printed)
     * @return     (itself)
     */
    CInterface & PrintChar ( char c );

    /**
     * Method that changes the color of the text printed in console.
     *
     * @param color     (color to be changed)
     * @return          (itself)
     */
    CInterface & GetColor ( EColors color );

    std::istream & m_In;
    std::ostream & m_Out;
    /** length of the line that is printed by some methods */
    size_t m_LineLength = 70;
};