/*      entity.cpp
 *
 *
 *
 */
#include "entity.h"

// todo : comment
Entity::Entity(Sprite* sprite, vec2 position, double speed, double accel, double max_speed)
{
    m_sprite    = sprite;
    
    m_position  = position;
    m_move_delta= speed;
    m_acceleration = accel;
    m_max_speed = max_speed;
    m_last_pos  = position;
    m_last_move_time = timestamp();
    m_time_since_update = 0;
    m_static    = speed == 0;
    
    // set the size of our collider
    set_collider_size(m_sprite->get_sprite_size());
}

void Entity::create_animation(std::string name, std::vector<int> clips)
{
    m_sprite->push_back_animation(name, clips);
}

void Entity::create_animation(std::string name, int first, int last)
{
    m_sprite->push_back_animation(name, first, last);
}

void Entity::draw()
{
    m_moving = math::make_positive(m_velocity.x) != 0;
    
    // make member variable
    static bool moving_last = m_moving;
    
    if(m_moving || timestamp() - m_last_move_time < 100 || moving_last)
    {
        if(math::make_positive(m_velocity.x) > 20)
            m_sprite->animate(m_position, ANIM_RUN);
        else
            m_sprite->animate(m_position, ANIM_WALK);        
    }
    else if(!m_moving)
    {
        m_sprite->animate(m_position, ANIM_IDLE);
    }
    
    m_last_pos  = m_position;
    moving_last = m_moving;
}

void Entity::update()
{
    this->update_movement();
    
    // keep in the camera bounds
    if(m_position.x > 800)
        m_position.x = 0;
    else if(m_position.x < 0)
        m_position.x = 800;
    
}

/*
 *  update_movement_hook
 *  Called from update_movement, just so we dont need to rewrite the function
 */
void Entity::update_movement_hook(vec2 delta)
{
    if(delta.x > 0)
        m_sprite->set_flip(SDL_FLIP_HORIZONTAL);
    
    else if(delta.x < 0)
        m_sprite->set_flip(SDL_FLIP_NONE);
}
