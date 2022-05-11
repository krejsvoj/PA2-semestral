/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 27.05.2021
 */

#include "CInterface.h"
using namespace std;

CInterface::CInterface(std::istream &in, std::ostream &out)
        : m_In (in),
          m_Out (out)
{
    m_In.exceptions( std::ios::badbit | std::ios::eofbit );
    m_Out.exceptions( std::ios::failbit | std::ios::badbit | std::ios::eofbit );
}

CInterface &CInterface::ClearInput() {
    // This code is not mine - author: David Bernhauer <bernhdav@fit.cvut.cz>
    m_In.clear ();
    m_In.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    return * this;
}

CInterface &CInterface::ClearConsole() {
    system("clear");
    return *this;
}

CInterface &CInterface::loadCommand(std::string &command) {
    m_In.clear();
    m_In >> command;
    ClearInput();
    if (m_In.fail())
        throw std::runtime_error ( UNEXPECTED_ERROR_RUNNING );
    StringToLower(command);
    return *this;
}

CInterface &CInterface::PromptMessage(const std::string &message, EColors color) {
    GetColor(color);
    m_Out << message;
    GetColor(EColors::RESET);
    return *this;
}

CInterface &CInterface::PromptHelpMessage (const std::string & help, const std::string & helpMessage) {
    PromptMessage (help, EColors::RED);
    m_Out << " - ";
    PromptMessage (helpMessage, EColors::WHITE);
    m_Out << endl;
    return *this;
}

CInterface &CInterface::PromptFileCorrupted() {
    ClearConsole().PrintMenu(EColors::BRIGHT_RED)
            .PromptMessage(FILE_CORRUPTED, EColors::BRIGHT_RED);

    return *this;
}

CInterface &CInterface::PrintMenu(EColors color) {
    PrintLineText(MAIN_MENU, color);
    PromptMessage(NEW_GAME_INFO, color);
    PrintLine(color);
    return *this;
}

CInterface &CInterface::PrintInfo() {
    PrintLineText(GAME_INFO, EColors::CYAN);
    PrintChar('#').PromptMessage(BORDER_INFO, EColors::WHITE);
    PrintChar('X').PromptMessage(CLAY_INFO, EColors::WHITE);
    PrintChar('x').PromptMessage(CLAY_SEMI_DESTROYED_INFO, EColors::WHITE);
    PrintChar('C').PromptMessage(ROCK_INFO, EColors::WHITE);
    PrintChar('c').PromptMessage(ROCK_SEMI_DESTROYED_INFO, EColors::WHITE);
    PrintChar('L').PromptMessage(LAVA_INFO, EColors::WHITE);
    PrintChar('A').PromptMessage(AIR_INFO, EColors::WHITE);
    PrintChar('<').PrintChar('>').PrintChar('v').PrintChar('^').PromptMessage(HUMAN_INFO, EColors::WHITE);
    PrintChar('{').PrintChar('}').PromptMessage(MONSTER_INFO, EColors::WHITE);
    PromptMessage(MONSTER_STATS_INFO, EColors::BRIGHT_RED);
    PrintLine (EColors::CYAN);
    return *this;
}

CInterface &CInterface::PrintStats(const CStats & stats) {
    PrintLineText("STATS", EColors::CYAN);
    GetColor(EColors::GREEN);
    m_Out << "Level: " << stats.m_Level << " | Energy: " << stats.m_Energy;
    m_Out << " | HP: " << stats.m_HP << " | Armor: " << stats.m_Armor << " | Points: " << stats.m_Points << endl;
    GetColor(EColors::YELLOW);
    m_Out << "Using: " << stats.m_ItemName << " (Damage ~ " << stats.m_ItemDamage << ")\u001b[0m" << endl;
    GetColor(EColors::BRIGHT_MAGENTA);
    m_Out << "Second weapon: " << stats.m_SecondItemName << " (Damage ~ " << stats.m_SecondItemDamage << ")" << endl;
    GetColor(EColors::RESET);

    return *this;
}

CInterface &CInterface::PrintLineText (const string &message, EColors color ) {

    GetColor(color);
    size_t count = 0;
    size_t length = ( m_LineLength - 2 - message.length() ) / 2;
    for ( ; count < length; count++)
        m_Out << "-";

    m_Out << " " << message << " ";
    for ( ; count < length * 2; count++)
        m_Out << "-";

    count += message.length() + 2;
    if (count < m_LineLength)
        m_Out << "-";
    GetColor(EColors::RESET);
    m_Out << endl;

    return *this;
}

CInterface &CInterface::PrintLine (EColors color) {
    GetColor(color);
    for (size_t i = 0; i < m_LineLength; ++i)
        m_Out << "-";
    m_Out << endl;
    GetColor(EColors::RESET);

    return *this;
}

CInterface & CInterface::PrintBuffer ( CBuffer & buffer ){
    for (size_t i = 0; i < buffer.m_MapHeight; ++i){
        for (size_t j = 0; j < buffer.m_MapWidth; ++j)
            PrintChar(buffer.m_Map[i][j]);
        m_Out << endl;
    }
    GetColor(EColors::RESET);
    PrintStats (*(buffer.m_Stats));

    return *this;
}

bool CInterface::PromptLoadFilename(fstream & input) {
    string filename;

    for (size_t i = 0; i < 5; ++i) {
        PromptMessage(ENTER_FILENAME, EColors::CYAN);
        loadCommand(filename);
        input.open (SAVED_MAPS_FOLDER + filename, fstream::in);
        if (input.good())
            return true;
        else PromptMessage(FILENAME_ERROR, EColors::BRIGHT_RED);
    }

    return false;
}

bool CInterface::SelectMap(fstream & input) {

    for (size_t i = 0; i < 5; ++i){
        PromptMessage(CHOSE_MAP, EColors::CYAN);
        string mapName;
        loadCommand (mapName);
        if ( mapName == "map1" ){
            input.open(MAP_FILENAME_1);
            return (input.good());
        }
        else if ( mapName == "map2" ){
            input.open(MAP_FILENAME_2);
            return (input.good());
        }
        else if ( mapName == "map3" ){
            input.open(MAP_FILENAME_3);
            return (input.good());
        }
        else if ( mapName == "map4" ){
            input.open(MAP_FILENAME_4);
            return (input.good());
        }
        else
            PromptMessage(UNKNOWN_MAP, EColors::BRIGHT_RED);
    }

    return false;
}

bool CInterface::PromptSaveFile(string & filename) {

    for (size_t i = 0; i < 5; ++i){
        fstream input;
        PromptMessage(ENTER_FILENAME, EColors::CYAN);
        loadCommand(filename);
        input.open(SAVED_MAPS_FOLDER + filename);
        if ( ! input.good() ){
            return true;
        }
        else
            PromptMessage(FILE_EXISTS_ERROR, EColors::BRIGHT_RED);
    }

    return false;
}

bool CInterface::PlayAgain(const string & what) {
    string command;

    PrintLine(EColors::BRIGHT_RED);
    PrintLineText(what, EColors::BRIGHT_RED);
    PrintLine(EColors::BRIGHT_RED);

    while (true) {
        PromptMessage(PLAY_AGAIN, EColors::CYAN);
        loadCommand(command);
        if (command == "yes")
            return true;
        if (command == "no")
            return false;
        else
            PromptMessage(UNKNOWN_COMMAND, EColors::BRIGHT_RED);
    }
}

std::string CInterface::GetCommand (const set<string> & knownCommands ) {

    string command;
    while (true) {
        PromptMessage(ENTER_COMMAND, EColors::CYAN);
        loadCommand(command);
        if ( knownCommands.find(command) != knownCommands.end ())
            return command;
        else PromptMessage(UNKNOWN_COMMAND, EColors::BRIGHT_RED);
    }
}

CInterface &CInterface::StringToLower(string &command){
    std::for_each (command.begin(), command.end(), [] (char & c){
        c = (char) tolower (c);
    });
    return *this;
}

CInterface &CInterface::PrintChar(char c) {
    switch (c) {
        case '#': GetColor(EColors::CYAN);                   m_Out << "#"; break;
        case 'X': GetColor(EColors::BACKGROUND_YELLOW);      m_Out << " "; GetColor (EColors::RESET); break;
        case 'x': GetColor(EColors::BACKGROUND_YELLOW);      m_Out << "▓"; GetColor (EColors::RESET); break;
        case '>': GetColor(EColors::GREEN);                  m_Out << "\033[5m>\033[25m"; break;
        case '<': GetColor(EColors::GREEN);                  m_Out << "\033[5m<\033[25m"; break;
        case '^': GetColor(EColors::GREEN);                  m_Out << "\033[5m^\033[25m"; break;
        case 'v': GetColor(EColors::GREEN);                  m_Out << "\033[5mv\033[25m"; break;
        case '{': GetColor(EColors::RED);                    m_Out << "\033[5m<\033[25m"; break;
        case '}': GetColor(EColors::RED);                    m_Out << "\033[5m>\033[25m"; break;
        case 'L': GetColor(EColors::BACKGROUND_RED);         m_Out << "▓"; GetColor (EColors::RESET); break;
        case 'A': GetColor(EColors::RESET);                  m_Out << " "; break;
        case 'C': GetColor(EColors::BACKGROUND_WHITE);       m_Out << " "; GetColor (EColors::RESET); break;
        case 'c': GetColor(EColors::BACKGROUND_WHITE);       m_Out << "▓"; GetColor (EColors::RESET); break;
        default : break;
    }

    return *this;
}

CInterface &CInterface::GetColor (EColors color) {
    switch (color) {
        case BLACK:             m_Out << "\u001b[30m";   break;
        case RED :              m_Out << "\u001b[31m";   break;
        case GREEN :            m_Out << "\u001b[32m";   break;
        case YELLOW :           m_Out << "\u001b[33m";   break;
        case BLUE :             m_Out << "\u001b[34m";   break;
        case MAGENTA :          m_Out << "\u001b[35m";   break;
        case CYAN :             m_Out << "\u001b[36m";   break;
        case WHITE :            m_Out << "\u001b[37m";   break;
        case BRIGHT_BLACK :     m_Out << "\u001b[30;1m"; break;
        case BRIGHT_RED :       m_Out << "\u001b[31;1m"; break;
        case BRIGHT_GREEN :     m_Out << "\u001b[32;1m"; break;
        case BRIGHT_YELLOW :    m_Out << "\u001b[33;1m"; break;
        case BRIGHT_BLUE :      m_Out << "\u001b[34;1m"; break;
        case BRIGHT_MAGENTA :   m_Out << "\u001b[35;1m"; break;
        case BRIGHT_CYAN :      m_Out << "\u001b[36;1m"; break;
        case BRIGHT_WHITE :     m_Out << "\u001b[37;1m"; break;
        case BACKGROUND_YELLOW: m_Out << "\u001b[43m\u001b[30m"; break;
        case BACKGROUND_RED:    m_Out << "\u001b[41m\u001b[30m"; break;
        case BACKGROUND_WHITE:  m_Out << "\u001b[47m\u001b[30m"; break;
        case RESET :            m_Out << "\u001b[0m";    break;
        default: break;
    }
    return *this;
}

