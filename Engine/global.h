/*
 *  global.h
 *  Included everywhere
 */
#pragma once

// these are used everywhere, all other headers are included in the need .h file
#include <array>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>

// todo : rewrite logger
#include "logger.h"

// todo : rename file
#include "game_defs.h"

// todo : move to definitions file
typedef long long timestamp_t;


// not really needed, maybe move elsewhere
extern int g_tick;


/*
 *  print_sdl_error
 *  Prints the sdl error to the console, only for debugging
 *
 */
inline void print_sdl_error(std::string func)
{
    error(func + " : " + std::string(SDL_GetError()));
}
