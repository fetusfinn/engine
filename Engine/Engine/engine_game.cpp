/*      engine_game.cpp
 *
 *  Engine functions that are written by the programmer
 *  Executes all the game code
 *
 */
#include "engine.h"
#include "player.h"
#include "tilemap.h"

Player* g_player;
// Tilemap* g_tiles;

Collidable* left_collider;
Collidable* right_collider;
Collidable* top_collider;
Collidable* bottom_collider;

static timestamp_t time_since_last_key_down = 0;
static SDL_Keycode last_key_down = SDLK_SPACE;
static bool move_key_down[4] = { false, false, false, false }; // w, a, s, d

/*
 *  on_init
 *  Called after the core engine has been initialised
 *  Initialises all game code
 */
void Engine::on_init()
{
    g_player = new Player(new Sprite(ASSETS_SPRITES + "player.png", 26), "player", {350, 250}, 2, 1.5f);
    g_player->create_animation(ANIM_WALK, 2, 16);
    g_player->create_animation(ANIM_IDLE, 0,  1);
    g_player->create_animation(ANIM_RUN,  2, 16); // same as walk for now
    
    m_window->set_background(WINDOW_BACKGROUND);
    
    top_collider    = new Collidable(0,     225, 800,   10, ColliderShape::ColliderRect, true);
    bottom_collider = new Collidable(0,     325, 800,   10, ColliderShape::ColliderRect, true);
    left_collider   = new Collidable(0,     234, 10,    92, ColliderShape::ColliderRect, true);
    right_collider  = new Collidable(790,   234, 10,    92, ColliderShape::ColliderRect, true);    
}

/*
 *  on_key_down
 *  Called on a key down event
 *  todo : move to player class
 */
static void on_key_down(SDL_Keycode key)
{
    // only jump when on ground || if have double jump item
    if((key == SDLK_SPACE || move_key_down[0]) && true) // g_player->is_colliding(CollisionBottom)
    {
        g_player->add_movement(0, -10);
        move_key_down[0] = true;
    }
    else if(key == SDLK_a || key == SDLK_LEFT || move_key_down[1])
    {
        g_player->add_movement(-1, 0);
        move_key_down[1] = true;
    }
    else if(key == SDLK_d || key == SDLK_RIGHT || move_key_down[3])
    {
        g_player->add_movement( 1, 0);
        move_key_down[3] = true;
    }
    else if(key == SDLK_UP)
    {
        g_player->add_movement(0, -1);
    }
    else if(key == SDLK_DOWN && !g_player->is_colliding(CollisionBottom))
    {
        g_player->add_movement(0, 1);
    }
}

/*
 *  on_event
 *  Handles events
 */
void Engine::on_event(SDL_Event* event, const uint8_t* keyboard_state)
{
    if(event->type == SDL_KEYDOWN)
    {
        auto key = event->key.keysym.sym;
        
        if(key == SDLK_DELETE)
            this->quit();
        
        on_key_down(key);
        
        last_key_down = key;
        time_since_last_key_down = timestamp();
    }
}

/*
 *  on_render
 *  Renders all game things
 */
void Engine::on_render()
{
    Tilemap* g_tiles = new Tilemap(ASSETS_TILES + "dirt.png");
    
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 15; y++)
        {
            g_tiles->render((x * 16) + 100, (y * 16) + 100, x * y);
        }
    }
    
    delete g_tiles;
    
    
    
    /*
    left_collider   ->draw_collision_box();
    right_collider  ->draw_collision_box();
    top_collider    ->draw_collision_box();
    bottom_collider ->draw_collision_box();
     
    g_player->draw();
    g_player->draw_collision_box();
    g_player->draw_info(m_renderer);
    */
}

/*
 *  on_update
 *
 */
void Engine::on_update()
{
    // keep moving
    if(timestamp() - time_since_last_key_down < 50)
    {
        on_key_down(last_key_down);
    }
    // havent had input for 50ms so reset movement key states
    else
    {
        move_key_down[0] = false;
        move_key_down[1] = false;
        move_key_down[2] = false;
        move_key_down[3] = false;
    }
    
    g_player->update();
    g_player->reset_collisions();
    
    Collidable::update_collisions();
}

/*
 *  on_shutdown
 *
 */
void Engine::on_shutdown()
{
    
}
