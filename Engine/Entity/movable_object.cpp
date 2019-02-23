/*      movable_object.cpp
 *
 *  
 *
 */
#include "movable_object.h"

std::unordered_map<int, MovableObject*> MovableObject::s_objects;

MovableObject::MovableObject(vec2 position, double speed, double accel, double max_speed)
{
    m_index         = (int)s_objects.size();
    
    m_position      = position;
    m_last_pos      = position;
    m_acceleration  = accel;
    m_velocity      = vec2(0, 0);
    m_move_delta    = speed;
    m_max_speed     = max_speed;
    m_moving        = false;
    
    m_last_move_time    = timestamp();
    m_time_since_update = 0;
    m_time_since_input  = 0;
    m_last_update_tick  = g_tick;
    
    s_objects.insert(std::make_pair(m_index, this));
}

/*
 *  add_movement
 *  Adds a new movement to the move list
 */
void MovableObject::add_movement(vec2 delta, timestamp_t time)
{
    m_move_list.push_back({delta, time});
}

/*
 *  add_movement
 *  Adds a new movement to the move list
 */
void MovableObject::add_movement(float x, float y)
{
    this->add_movement(vec2(x, y));
}

/*
 *  clear_moves
 *  Clears the move list
 */
void MovableObject::clear_moves()
{
    m_move_list.clear();
}

/*
 *  update_movement
 *  Updates movement for the current tick
 */
void MovableObject::update_movement()
{
    // process movements
    this->move();
    
    // apply gravity
    this->apply_gravity();
    
    // give the engine time to fully catch up on our movement
    // before we clear the move list
    if(timestamp() - m_time_since_input > 50)
        this->clear_moves();
    
    m_time_since_update = timestamp() - m_last_move_time;
}

/*
 *  apply_gravity
 *  Applies gravity to the object
 */
void MovableObject::apply_gravity()
{
    static vec2 last_pos = m_position;
    
    // move the player down
    m_position.y += m_gravity;
    m_velocity.y  = last_pos.delta_vec(m_position).y;
    
    last_pos = m_position;
}

/*
 *  move
 *  Moves the object
 */
void MovableObject::move()
{
    vec2 delta = (m_move_list.size() > 0 ? m_move_list.at(0).delta : vec2(0, 0));
    
    if(!delta)
    {
        m_velocity = vec2(m_last_pos.delta_vec(m_position).x, m_last_pos.delta_vec(m_position).y);
        return;
    }
    
    // make the sprite face the right way
    update_movement_hook(delta);
    
    // accelerate the movement
    double accel = (math::make_positive(m_velocity.x) < m_max_speed && math::make_positive(m_velocity.x) > 0) ? m_acceleration : 1.f;
    delta *= m_move_delta;
    delta *= accel;
    
    m_last_pos      = m_position;
    m_position     += delta;
    m_velocity      = vec2(-m_last_pos.delta_vec(m_position).x, m_last_pos.delta_vec(m_position).y);
    m_last_move_time= timestamp();
    m_time_since_input = m_move_list.at(0).time;
    m_last_update_tick = g_tick;
    
    // remove the first movement because we just did it
    m_move_list.erase(m_move_list.begin());
}

/*
 *
 *
 */
void MovableObject::on_collision_x(MovableObject* obj)
{
    
}

/*
 *
 *
 */
void MovableObject::on_collision_y(MovableObject* obj)
{
    
}
