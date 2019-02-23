/*
 *  movable_object.h
 */
#pragma once

#include <unordered_map>

#include "global.h"
#include "util.h"
#include "math.h"
#include "vec2.h"

// todo : rewrite, rename, Object, MovableObject, StaticObject
class MovableObject
{
private:
    
    static std::unordered_map<int, MovableObject*> s_objects;
    
    int m_gravity = 10;
    
protected:
    
    struct move_info_t
    {
        vec2 delta;
        timestamp_t time; // the time the move was created
    };
        
    int         m_index;
    vec2        m_position;
    vec2        m_last_pos;
    bool        m_static;
    vec2        m_velocity;
    double      m_acceleration;         // the amount the object is accelerated by
    double      m_move_delta;           // ammount of game units moved per screen unit
    double      m_max_speed;
    bool        m_moving;
    timestamp_t m_last_move_time;       // the timestamp of our last move
    timestamp_t m_time_since_update;    // the time since our last update
    timestamp_t m_time_since_input;     // the time since we last recieved input
    int         m_last_update_tick;     // the tick the last movement occured in
    
    // stacked movements for the current tick
    std::vector<move_info_t> m_move_list;
    
protected:
    
    virtual void move();
    virtual void update_movement();
    virtual void update_movement_hook(vec2 delta) { } // only used in Entity, basically a forward delc
    
    virtual void on_collision_x(MovableObject* obj);
    virtual void on_collision_y(MovableObject* obj);
    
    void clear_moves();
    
    void apply_gravity();
    
    void set_gravity(int gravity) { m_gravity = gravity; }
    
public:
    
    MovableObject() {};
    MovableObject(vec2 position, double speed = 3.f, double accel = 1.3, double max_speed = 20);
    
    // maybe make virtual, but not sure
    void add_movement(vec2 delta, timestamp_t time = timestamp());
    void add_movement(float x, float y);
    
    // getters
    vec2    get_position()  { return m_position; }
    vec2    get_velocity()  { return m_velocity; }
    bool    is_static()     { return m_static; }
    
    // setters
    void set_velocity(vec2 vel) { m_velocity = vel; }
    void set_position(vec2 pos) { if(!m_static) m_position = pos; } // only set pos if not a static object
    
};
