/*
 *  game_defs.h
 *
 *  Defines to make it easier to change things between projects
 *
 */
#pragma once

#define PWNED_DEBUG

#define ASSETS_FOLDER   std::string("./assets/")
#define ASSETS_TILES    ASSETS_FOLDER + std::string("Tiles/")
#define ASSETS_SPRITES  ASSETS_FOLDER + std::string("Sprites/")
#define ASSETS_FONTS    ASSETS_FOLDER + std::string("Fonts/")
#define ASSETS_SOUNDS   ASSETS_FOLDER + std::string("Sounds/")

#define WINDOW_TITLE    std::string("Window")
#define WINDOW_SIZE     vec2(800, 600)
#define WINDOW_BACKGROUND ASSETS_TILES + std::string("background.png")
