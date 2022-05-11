/**
 * @date 02.05.2021
 * @inspired_by David Bernhauer <bernhdav@fit.cvut.cz
 */

#pragma once
#include <string>
#include <functional>
#include <memory>
#include "CGame.h"
#include "CInterface.h"

/**
 * Class that represents represents individual commands in the application.
 *
 */

class CCommand {
public:

    /**
     * Constructor CCommand initializes the command according to the function loaded.
     *
     * @param help     (help for the command)
     * @param run      (function that is called when m_Run is called)
     */
    CCommand( std::string help, std::function<bool(CGame &)> run )
            : m_Help(std::move(help)),
              m_Run(std::move (run))
    {
    }

    /**
     * Method that prints help for the command into the interface
     * Method is made const because it only prints info, doesn't change anything.
     *
     * @param interface     (shared_ptr to the CInterface where the help should be printed)
     * @param commandName   (command name)
     */
    void GetHelp ( const std::shared_ptr<CInterface> & interface, const std::string & commandName ) const {
        interface->PromptHelpMessage(commandName, m_Help);
    }

    /**
     * Method that runs the function stored in m_Run variable. Functional library is used.
     * Method is made const because it doesn't change any variable.
     *
     * @param game      (game where the command makes changes)
     * @return          ( true / false depending on what the function returns)
     */
    bool RunCommand ( CGame & game ) const {
        return m_Run (game);
    }

private:
    std::string m_Help;
    std::function <bool ( CGame & )> m_Run;
};




