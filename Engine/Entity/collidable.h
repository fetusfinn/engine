/*
 *  collidable.h
 */
#pragma once

#include <unordered_map>

#include "global.h"
#include "movable_object.h"
#include "util.h"
#include "vec2.h"

// todo : MoveableObject -> know what to do

enum ColliderShape
{
    ColliderRect,
    ColliderCircle, // unused
};

enum CollisionSide
{
    CollisionLeft   = 0,
    CollisionRight  = 1,
    CollisionTop    = 2,
    CollisionBottom = 3,
};

class Collidable : public MovableObject
{
private:
    
    // just to store all the collidables in with a unique index
    static std::unordered_map<int, Collidable*> s_collidables;
    
    int             m_collider_index;
    vec2            m_size;
    ColliderShape   m_shape;
    std::array<bool, 4> m_colliding; // l, r, t, b
    
private:
    
    bool check_x_collision(Collidable* collider);
    bool check_y_collision(Collidable* collider);
    
protected:
    
    void set_collider_size(vec2 size)           { m_size  = size; }
    void set_collider_shape(ColliderShape shape){ m_shape = shape; }
    
public:
    
    static void update_collisions();
    
    Collidable();
    Collidable(vec2 pos, vec2 size, ColliderShape shape = ColliderRect, bool is_static = false);
    Collidable(float x, float y, float w, float h, ColliderShape shape = ColliderRect, bool is_static = false);
    
    void draw_collision_box();
    
    void reset_collisions() { m_colliding[0] = m_colliding[1] = m_colliding[2] = m_colliding[3] = false; }
    
    // getters
    int  get_index() { return m_index; }
    vec2 get_size()  { return m_size; }    
    ColliderShape get_shape()   { return m_shape; }
    bool is_colliding(int side) { return m_colliding.at(side); };
    
};
