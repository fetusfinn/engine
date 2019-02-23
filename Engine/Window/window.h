/*
 *  window.h
 */
#pragma once

#include "global.h"
#include "texture.h"
#include "vec2.h"

class Window
{
private:
    
    static Window* s_inst;
    
    std::string     m_title;
    vec2            m_size;
    SDL_Window*     m_window;
    
    Texture*        m_background_tex;

public:
    
    static Window* get() { return s_inst; }
    static Window* init(const std::string& title, vec2 size);
    
    Window(const std::string& title, vec2 size);
    ~Window();
    
    void on_render();
    void destroy() { SDL_DestroyWindow(m_window); }
    
    // setters
    void set_background(const std::string& path);
        
    // getters
    bool            is_valid()      { return m_window != nullptr; }
    vec2            get_size()      { return m_size; }
    SDL_Window*     get_window()    { return m_window; }
    
};
