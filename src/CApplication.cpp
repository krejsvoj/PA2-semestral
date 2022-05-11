/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CApplication.h"

using namespace std;

CApplication::CApplication(std::shared_ptr<CInterface> interface)
        : m_Interface ( std::move ( interface ) )
{
    m_Commands.insert ({"?", HelpCommand()});
    m_Commands.insert ({"exit", ExitCommand()});
    m_Commands.insert ({"new" , NewGameCommand()});
    m_Commands.insert ({"load", LoadGameCommand()});
    m_Commands.insert ({"play", PlayCommand ()});
    m_Commands.insert ({"save", SaveCommand()});
    m_Commands.insert ({"info", InfoCommand()});
    for (const auto & command : m_Commands)
        m_KnownCommands.insert(command.first);
}

int CApplication::Run() {

    CGame game (m_Interface);
    m_Interface->ClearConsole();

    while (true) {
        m_Interface->PrintMenu(EColors::BRIGHT_RED);
        string command;
        while (true) {
            try {
                command = m_Interface->GetCommand(m_KnownCommands);
                if (!m_Commands.find(command)->second.RunCommand(game)){
                    if (command == "exit")
                        return 0;
                    if ( ( command == "new" || command == "load" ) && m_MapLoaded ) {
                        m_Interface->PromptMessage(CAN_CONTINUE, EColors::CYAN)
                            .PrintLine(EColors::CYAN);
                    }
                }
            }
            catch (YouDiedException &) {
                if (PlayAgain(YOU_DIED_MESSAGE, game))
                    break;
                return 1;
            }
            catch (KilledByMonster &){
                if (PlayAgain(KILLED_BY_MONSTER_MESSAGE, game))
                    break;
                return 1;
            }
            catch (StepInLava &){
                if (PlayAgain(STEP_IN_LAVA, game))
                    break;
                return 1;
            }
        }
    }
}

bool CApplication::InitGame(CGame & game, fstream & input) {
    CGame newGame (m_Interface);
    if ( newGame.Init(input) ) {
        m_MapLoaded = true;
        game = std::move (newGame);
        m_Interface->PrintLine(EColors::CYAN)
                .PromptMessage(MAP_LOADED, EColors::CYAN);
    }
    else {
        m_Interface->PromptFileCorrupted();
        return false;
    }
    return true;
}

CCommand CApplication::PlayCommand() {
    return CCommand {
            PLAY_COMMAND_HELP,
            [this] (CGame & game) {
                if (! m_MapLoaded) {
                    m_Interface->PromptMessage(NONE_MAP_LOADED, EColors::BRIGHT_RED);
                    return false;
                }
                while (true){
                    if (!game.Tick())
                        return true;
                }
            }};
}

CCommand CApplication::NewGameCommand() {

    return CCommand {
            NEW_GAME_COMMAND_HELP ,
            [this] (CGame & game) {
                m_Interface->ClearConsole()
                        .PrintLineText(CREATING_GAME, EColors::CYAN);
                fstream input;
                if ( ! m_Interface->SelectMap(input) ) {
                    m_Interface->ClearConsole().PrintMenu(EColors::BRIGHT_RED)
                            .PromptMessage(CREATING_GAME_FAILED, EColors::BRIGHT_RED);
                    return false;
                }
                return InitGame (game, input);
            }};
}

CCommand CApplication::HelpCommand() const {
    return CCommand {
            APP_COMMAND_HELP_HELP,
            [this] (CGame &) {
                m_Interface->PrintLineText (KNOWN_COMMANDS, EColors::CYAN);
                for (auto &command : m_Commands)
                    command.second.GetHelp (m_Interface, command.first);
                m_Interface->PrintLine (EColors::CYAN);
                return true;
            }};
}

CCommand CApplication::LoadGameCommand() {
    return CCommand {
            LOAD_COMMAND_HELP,
            [this] (CGame & game) {
                m_Interface->ClearConsole()
                        .PrintLineText(LOADING_GAME, EColors::CYAN);
                fstream input;
                if ( ! m_Interface->PromptLoadFilename(input) ) {
                    m_Interface->ClearConsole().PrintMenu(EColors::BRIGHT_RED)
                            .PromptMessage(LOADING_FAILED, EColors::BRIGHT_RED);
                    return false;
                }
                return InitGame (game, input);
            }};
}

CCommand CApplication::SaveCommand() {
    return CCommand {
        SAVE_COMMAND_HELP,
        [this] (CGame & game) {
            if ( ! m_MapLoaded ){
                m_Interface->PromptMessage(NONE_MAP_LOADED, EColors::BRIGHT_RED);
                return false;
            }
            string filename;
            if ( m_Interface->PromptSaveFile(filename) ) {
                game.redrawConsole();
                game.SaveGame(filename);
                m_Interface->PrintLineText(GAME_PAUSED, EColors::CYAN)
                    .PromptMessage(MAP_SAVED, EColors::BRIGHT_GREEN);
                return true;
            }
            else {
                game.redrawConsole();
                m_Interface->PrintLineText(GAME_PAUSED, EColors::CYAN)
                    .PromptMessage(FAILED_TO_SAVE, EColors::BRIGHT_RED);
                return false;
            }
    }};
}

CCommand CApplication::ExitCommand(){
    return CCommand {
        EXIT_COMMAND_HELP,
        [] (CGame &) {
            return false;
    }};
}

CCommand CApplication::InfoCommand() {
    return CCommand {
       INFO_COMMAND_HELP,
        [this] (CGame &) {
           m_Interface->PrintInfo ();
           return true;
    }};
}

bool CApplication::PlayAgain(const string & what, CGame & game) {

    if (m_MapLoaded)
        game.redrawConsole();
    if (m_Interface->PlayAgain(what)) {
        m_MapLoaded = false;
        m_Interface->ClearConsole();
        return true;
    }
    return false;
}
