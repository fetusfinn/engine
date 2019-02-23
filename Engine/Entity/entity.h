/*
 *  entity.h
 */
#pragma once

#include "global.h"
#include "collidable.h"
#include "texture.h"
#include "sprite.h"
#include "util.h"
#include "vec2.h"

class Entity : public Collidable
{
protected:
    
    Sprite* m_sprite;
        
    bool    m_visible;
    
protected:
    
public:
    
    Entity() { }
    Entity(Sprite* sprite, vec2 position, double speed = 3.f, double accel = 1.3, double max_speed = 20);
    ~Entity() { delete m_sprite; }
    
    void create_animation(std::string name, int first, int last);
    void create_animation(std::string name, std::vector<int> clips);
    
    void draw();
    void update();
    
    void update_movement_hook(vec2 delta);
    
};
