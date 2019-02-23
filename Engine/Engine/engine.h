/*
 *  engine.h
 */
#pragma once

#include "global.h"
#include "window.h"
#include "texture.h"
#include "util.h"
#include "renderer.h"

class Engine
{
private:
    
    static Engine* s_inst;
    
    // todo : create window class
    Window*         m_window;
    
    // todo : renderer class
    SDL_Renderer*   m_renderer;
    
    bool            running;
    int             tick;
    unsigned int    m_speed; // unused
    
    // whether or not each module has been init yet
    bool            sdl_init, ttf_init, img_init;
    
    // todo : move
    struct
    {
        unsigned int old_time;
        unsigned int last_time;
        
        unsigned int m_fps;
        unsigned int frames;
        
        float speed_factor;
        
        void on_update()
        {
            if (old_time + 1000 < SDL_GetTicks())
            {
                old_time = SDL_GetTicks();
                m_fps = frames;
                frames = 0;
            }
            
            speed_factor = ((SDL_GetTicks() - last_time) / 1000.0f) * 32.0f;
            last_time = SDL_GetTicks();
            frames++;
        }
    }m_fps;
    
private:
    
    // core engine functions
    void handle_events();
    void update();
    void quit() { this->running = false; }
    
    // functions that are written by the user for their project
    void on_init();
    void on_event(SDL_Event* event, const uint8_t* keyboard_state);
    void on_render();
    void on_update();
    void on_shutdown();
    
public:
    
    static Engine* get() { if(!s_inst) s_inst = new Engine(); return s_inst; }
    
    bool init();
    void run();
    void shutdown();
    
    // setters
    void set_speed(double new_speed) { this->m_speed = new_speed; };
    
    // getters
    SDL_Renderer* get_renderer() { return m_renderer; }
};
