/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 30.05.2021
 * @inspired_by David Bernhauer <bernhdav@fit.cvut.cz
 */

#pragma once

#include <string>
#include <functional>
#include <memory>
#include "CMap.h"
#include "CInterface.h"

/**
 * @brief
 * Class that represents game command for human player.
 *
 */
class CGameCommand {
public :

    /**
     * Constructor CGameCommand initializes the command according to the function loaded.
     *
     * @param help      (help for the command)
     * @param run       (function that is called when m_Run is called)
     */
    CGameCommand ( std::string help, std::function<bool (CMap &)> run)
        : m_Help ( std::move (help) ),
        m_Run (std::move (run))
    {
    }

    /**
     * Method that prints help for the command into the interface
     * Method is made const because it only prints help, does not change variables.
     *
     * @param interface     (shared_ptr to the CInterface where the help should be printed)
     * @param commandName   (command name)
     */
    void GetHelp (const std::shared_ptr<CInterface> & interface, const std::string & commandName) const {
        interface->PromptHelpMessage(commandName, m_Help);
    }

    /**
     * Method that runs the function stored in m_Run variable. <functional> library is used.
     *
     * @param map        (map where the command can make changes)
     * @return           (true/false depending on what the function returns)
     */
    bool RunCommand ( CMap & map ) const {
        return m_Run (map);
    }

private:
    std::string m_Help;
    std::function <bool ( CMap & )> m_Run;
};
