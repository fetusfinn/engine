/*      collidable.cpp
 *
 *
 *
 */
#include "collidable.h"
#include "engine.h"

std::unordered_map<int, Collidable*> Collidable::s_collidables;

Collidable::Collidable()
{
    m_collider_index = (int)s_collidables.size();
    m_size      = vec2(0, 0);
    m_shape     = ColliderRect;
    m_static    = false;
    
    insert_into_map(Collidable::s_collidables, m_collider_index, this);
}

Collidable::Collidable(vec2 pos, vec2 size, ColliderShape shape, bool is_static)
{
    m_collider_index = (int)s_collidables.size();
    m_position  = pos;
    m_size      = size;
    m_shape     = shape;
    m_static    = is_static;
    
    insert_into_map(Collidable::s_collidables, m_collider_index, this);
}

Collidable::Collidable(float x, float y, float w, float h, ColliderShape shape, bool is_static)
{
    m_collider_index = (int)s_collidables.size();
    m_position  = vec2(x, y);
    m_size      = vec2(w, h);
    m_shape     = shape;
    m_static    = is_static;
    
    insert_into_map(Collidable::s_collidables, m_collider_index, this);
}

/*
 *  update_collisions
 *  Collides all obects
 */
void Collidable::update_collisions()
{
    size_t num_colliders = s_collidables.size();
    
    for(int i = 0; i < num_colliders; i++)
    {
        Collidable* col_1 = s_collidables.at(i);
        
        if(!col_1)
            continue;
        
        if(col_1->is_static())
            continue;

        // col_1->reset_collision();
        
        vec2 col_1_pos  = col_1->get_position();
        vec2 col_1_size = col_1->get_size();
        
        for(int j = 0; j < num_colliders; j++)
        {
            Collidable* col_2 = s_collidables.at(j);
            
            if(!col_2)
                continue;
            
            if(col_1 == col_2)
                continue;
            
            vec2 col_2_pos  = col_2->get_position();
            vec2 col_2_size = col_2->get_size();
            
            // todo : we should be using add_movement instead of set_position
            // todo : determine what side we are colliding on when we are moving at a high speed, check velocity
            
            if(col_1->check_x_collision(col_2))
            {
                // amount to move the object
                // float move_amount = 0.f; // todo
                
                bool colliding_on_top_bot = col_1->is_colliding(CollisionTop) || col_1->is_colliding(CollisionBottom);
                
                // if on right side, not working
                if(col_1->is_colliding(CollisionRight)) // col_1_pos.x + col_1_size.x >= col_2_pos.x && col_1_pos.x < col_2_pos.x
                    col_1->set_position(vec2(col_2_pos.x - col_1_size.x, col_1_pos.y));
                
                else
                    col_1->set_position(vec2(col_2_pos.x + col_2_size.x, col_1_pos.y));
                
                col_1->on_collision_x(col_2);
            }
            
            if(col_1->check_y_collision(col_2))
            {
                // amount to move the object
                // float move_amount = 0.f; // todo
                
                bool colliding_on_side = col_1->is_colliding(CollisionRight) || col_1->is_colliding(CollisionLeft);
                
                // if we are colliing on the bottom
                if(col_1->is_colliding(CollisionBottom) && !colliding_on_side)
                    col_1->set_position(vec2(col_1_pos.x, col_2_pos.y - col_1_size.y));
                
                else if(!colliding_on_side)
                    col_1->set_position(vec2(col_1_pos.x, col_2_pos.y + col_2_size.y));
                
                col_1->on_collision_y(col_2);
            }
        }
    }
}

/*
 *  check_x_collision
 *
 */
bool Collidable::check_x_collision(Collidable* col)
{
    ColliderShape col_shape = col->get_shape();
    
    // Rect vs rect
    if(m_shape == ColliderRect && m_shape == col_shape)
    {
        vec2 col_size = col->get_size();
        vec2 col_pos  = col->get_position();
        
        float our_left  = m_position.x;
        float our_right = m_position.x + m_size.x;
        float col_left  = col_pos.x;
        float col_right = col_pos.x + col_size.x;
        
        // todo : check if above or under, if so then return
        
        // collider is under us
        if(m_position.y + m_size.y <= col_pos.y)
            return false;
        
        // collider is above us
        if(m_position.y >= col_pos.y + col_size.y)
            return false;
        
        // collision on left side
        if(our_left <= col_right && our_right > col_right)
        {
            m_colliding[0] = true;
            return true;
        }
        
        // collision on right side
        if(our_right >= col_left && our_left < col_left)
        {
            m_colliding[1] = true;
            return true;
        }
    }
    
    // Circle vs circle
    else if(m_shape == ColliderCircle && m_shape == col_shape)
    {
        
    }
    
    // Rect vs circle
    else
    {
        
    }
    
    return false;
}

/*
 *  check_collision
 *
 */
bool Collidable::check_y_collision(Collidable* col)
{
    ColliderShape col_shape = col->get_shape();
    
    // Rect vs rect
    if(m_shape == ColliderRect && m_shape == col_shape)
    {
        vec2 col_size = col->get_size();
        vec2 col_pos  = col->get_position();
        
        float our_top = m_position.y;
        float our_bot = m_position.y + m_size.y;
        float col_top = col_pos.y;
        float col_bot = col_pos.y + col_size.y;
        
        // collider is to the left
        if(m_position.x > col_pos.x + col_size.x)
            return false;
        
        // collider is to the right
        if(m_position.x + m_size.x < col_pos.x)
            return false;
        
        // todo : check if to the side, if so then return
        
        // for some reason these are the wrong way around
        
        // collision on top
        if(our_top <= col_bot && our_bot > col_bot)
        {
            m_colliding[2] = true;
            return true;
        }
        
        // collision on bottom
        if(our_bot >= col_top && our_top < col_top)
        {
            m_colliding[3] = true;
            return true;
        }
    }
    
    // Circle vs circle
    else if(m_shape == ColliderCircle && m_shape == col_shape)
    {
        
    }
    
    // Rect vs circle
    else
    {
        
    }
    
    return false;
}

/*
 *  draw_collision_box
 *  Draws the bounds of the collider
 */
void Collidable::draw_collision_box()
{
    SDL_Renderer* renderer = Engine::get()->get_renderer();
    SDL_Rect rect = {(int)m_position.x, (int)m_position.y, (int)m_size.x, (int)m_size.y};
    SDL_Color col = {255, 0, 0};
    
    SDL_SetRenderDrawColor(renderer, col.r, col.g, col.g, 255);
    
    if(SDL_RenderDrawRect(renderer, &rect) < 0)
        print_sdl_error("SDL_RenderDrawRect");
}
