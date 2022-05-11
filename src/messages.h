/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 01.06.2021
 */

#pragma once

// CHumanPlayer messages
const char * const MOVE_LEFT_HELP = "moves your player to the left";
const char * const MOVE_RIGHT_HELP = "moves your player to the right";
const char * const PLAYER_HELP_COMMAND = "prints info for each command";
const char * const PAUSE_HELP = "pauses the game - opens main menu";
const char * const JUMP_HELP = "your player jumps in the air";
const char * const HIT_DOWN_HELP = "hits the block under your player";
const char * const HIT_UP_HELP = "hits the block on top of your player";
const char * const HIT_LEFT_HELP = "hits the block to the left of your player";
const char * const HIT_RIGHT_HELP = "hits the block to the right of your player";
const char * const SWAP_WEAPONS_HELP = "swap weapons";
const char * const KNOWN_GAME_COMMANDS = "KNOWN GAME COMMANDS";
const char * const CANT_JUMP_WARNING = "Cannot jump in the air\n";
const char * const OUT_OF_ENERGY_WARNING = "You dont have enough energy to hit blocks\n";
const char * const PICKAXE = "Pickaxe";
const char * const SWORD = "Sword";
const char * const PLACE_BLOCK_HELP = "places a block of clay under your player \n\t- the block must be placed on an object\n\t- there must be air under your player";
const char * const PLACE_BLOCK_ERROR = "Cannot place an object\n";
const char * const KILLED_BY_MONSTER_MESSAGE = "YOU DIED - You were killed by a monster";
const char * const STEP_IN_LAVA = "YOU DIED - You step in lava";

// CInterface messages
const char * const MAIN_MENU = "MAIN MENU";
const char * const UNEXPECTED_ERROR_RUNNING = "Unexpected error while reading input";
const char * const ENTER_COMMAND = "Enter your command (\"?\" for help): ";
const char * const UNKNOWN_COMMAND = "Unknown command.\n";
const char * const NEW_GAME_INFO = "Enter 'new' to start a new game or 'load' to load a game from a file.\n";
const char * const PLAY_AGAIN = "Do you wanna play again? 'yes' or 'no': ";
const char * const FILENAME_ERROR = "File doesn't exist! Enter filename again.\n";
const char * const SAVED_MAPS_FOLDER = "examples/maps/saved_maps/";
const char * const CLAY_INFO = "\t represents a block of clay\n";
const char * const CLAY_SEMI_DESTROYED_INFO = "\t represents a semi destroyed block of clay\n";
const char * const GAME_INFO = "GAME INFO";
const char * const LAVA_INFO = "\t represents a block of lava\n";
const char * const AIR_INFO = "\t (nothing) represents block of air\n";
const char * const HUMAN_INFO = "\t represents human player (his direction)\n";
const char * const MONSTER_INFO = "\t represents monster player (his direction)\n";
const char * const ROCK_INFO = "\t represents a block of rock\n";
const char * const ROCK_SEMI_DESTROYED_INFO = "\t represents a semi destroyed block of rock\n";
const char * const BORDER_INFO = "\t represents a border of the map (block cannot be destroyed)\n";
const char * const MONSTER_STATS_INFO = "\n*WARNING* Be careful - monsters are strong\n*WARNING* You need to reach at least level 5 to kill monsters\n";

// CApplication messages
const char * const PLAY_COMMAND_HELP = "enter the game mode (map has to be loaded)";
const char * const EXIT_COMMAND_HELP = "quits the game";
const char * const NEW_GAME_COMMAND_HELP = "creates a new game";
const char * const NONE_MAP_LOADED = "None map is loaded, please create or load a game.\n";
const char * const CREATING_GAME = "CREATING NEW GAME";
const char * const MAP_LOADED = "The map is loaded, enter \"play\" to start the game.\n";
const char * const CREATING_GAME_FAILED = "Creating new game failed, try again\n";
const char * const APP_COMMAND_HELP_HELP = "prints info for each command";
const char * const KNOWN_COMMANDS = "KNOWN COMMANDS";
const char * const LOAD_COMMAND_HELP = "loads a game from a file";
const char * const LOADING_GAME = "LOADING GAME";
const char * const LOADING_FAILED = "Loading game failed\n";
const char * const FILE_CORRUPTED = "Loading map failed. The map file is corrupted.\n";
const char * const UNKNOWN_MAP = "Unknown map\n";
const char * const CHOSE_MAP = "Chose one of 4 maps [map1, map2, map3, map4]: ";
const char * const CAN_CONTINUE = "You can still continue in your last game by entering 'play'\n";
const char * const MAP_FILENAME_1 = "examples/maps/created_maps/map1";
const char * const MAP_FILENAME_2 = "examples/maps/created_maps/map2";
const char * const MAP_FILENAME_3 = "examples/maps/created_maps/map3";
const char * const MAP_FILENAME_4 = "examples/maps/created_maps/map4";
const char * const SAVE_COMMAND_HELP = "saves the game to a file (map has to be loaded)";
const char * const MAP_SAVED = "Map saved\n";
const char * const FAILED_TO_SAVE = "Failed to save file\n";
const char * const ENTER_FILENAME = "Enter filename: ";
const char * const FILE_EXISTS_ERROR = "File already exists. Please enter a non existing file. \n";
const char * const INFO_COMMAND_HELP = "prints info about the game";

// CGame messages
const char * const GAME_MODE = "GAME MODE";
const char * const MAP_INFO = "MAP_INFO";
const char * const END_MAP_INFO = "END_OF_MAP_INFO";
const char * const PLAYERS = "PLAYERS";
const char * const PLAYER_HUMAN = "PLAYER_HUMAN";
const char * const PLAYER_MONSTER = "PLAYER_MONSTER";
const char * const GAME_PAUSED = "MENU - GAME PAUSED";

// Exceptions messages
const char * const YOU_DIED_MESSAGE = "GAME OVER - You fell from a great height";

// main.cpp messages
const char * const UNEXPECTED_ERROR = "Unexpected error occurred while the program was running";