/*
 *  player.h
 */
#pragma once

#include "global.h"
#include "entity.h"
#include "renderer.h"

class Player : public Entity
{
private:
    
    // player info
    std::string m_name;                 
    
public:
    
    Player(Sprite* sprite, std::string name, vec2 position, double speed = 2.f, double accel = 1.3, double max_speed = 20);    
    
    void draw_info(SDL_Renderer* renderer);
    
};
