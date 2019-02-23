/*      player.cpp
 *
 *  note : currently this is more of a player class rather than an Player one
 *
 */
#include "player.h"

Player::Player(Sprite* sprite, std::string name, vec2 position, double speed, double accel, double max_speed)
{
    m_sprite    = sprite;
    m_name      = name;
    m_position  = position;
    m_move_delta= speed;    //
    m_velocity  = vec2();
    m_acceleration = accel;
    m_max_speed = max_speed;
    m_last_pos  = position;
    m_last_move_time = timestamp();
    m_time_since_update = 0;
    m_static    = speed == 0;
    
    // set the size of our collider
    set_collider_size(m_sprite->get_sprite_size());
}

/*
 *  draw_info
 *
 */
void Player::draw_info(SDL_Renderer* renderer)
{
    using namespace std;
    
    g_render->string(m_position.x, m_position.y - 20, to_string(m_position.x) + ", " + to_string(m_position.y), Fonts::large, SDL_COLOR_WHITE);
    
    g_render->string(10,  30, m_name, Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10,  50, "m_position : "       + to_string(m_position.x) + ", " + to_string(m_position.y), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10,  70, "m_move_delta : "     + to_string(m_move_delta), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10,  90, "m_acceleration : "   + to_string(m_acceleration), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10, 110, "m_max_speed : "      + to_string(m_max_speed), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10, 130, "m_velocity :"        + to_string(m_velocity.x) + ", " + to_string(m_velocity.y), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10, 150, "m_last_pos : "       + to_string(m_last_pos.x) + ", " + to_string(m_last_pos.y), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10, 170, "m_moving : "         + to_string(m_moving), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10, 190, "m_last_update_tick : "  + to_string(m_last_update_tick), Fonts::large, SDL_COLOR_WHITE);
    g_render->string(10, 210, "m_time_since_update : " + to_string(m_time_since_update), Fonts::large, SDL_COLOR_WHITE);
    
    string colliding_str = to_string(is_colliding(0)) + " " + to_string(is_colliding(1)) + " " + to_string(is_colliding(2)) + " " + to_string(is_colliding(3));
    g_render->string(10, 230, "m_colliding[] : " + colliding_str, Fonts::large, SDL_COLOR_WHITE);
}
