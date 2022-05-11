/**
 * @author Vojtech Krejsa <krejsvoj@fit.cvut.cz>
 * @date 01.06.2021
 */

#pragma once

#include "messages.h"

/** Specific exception that represents death of the human player. */
struct YouDiedException : public std::exception {};

/** Specific exception that represents human player being killed by a monster */
struct KilledByMonster : public std::exception {};

/** Specific exception that represents human player stepping in the lava */
struct StepInLava : public std::exception {};