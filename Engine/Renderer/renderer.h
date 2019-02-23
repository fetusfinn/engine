/*
 *  renderer.h
 */
#pragma once

#include "global.h"
#include "texture.h"

// move to color class
#define SDL_COLOR_WHITE SDL_Color({255, 255, 255, 255})
#define SDL_COLOR_BLACK SDL_Color({  0,   0,   0, 255})
#define SDL_COLOR_RED   SDL_Color({255,   0,   0, 255})
#define SDL_COLOR_GREEN SDL_Color({  0, 255,   0, 255})
#define SDL_COLOR_BLUE  SDL_Color({  0,   0, 255, 255})

typedef TTF_Font font_t;

enum FontFlags
{
    FONTFLAG_SOLID,
    FONTFLAG_SHADED,
    FONTFLAG_BLENDED,
};

namespace Fonts
{
    extern font_t* small;
    extern font_t* large;
    
    void init();
    void destroy();
};

class Renderer
{
private:
    
    static Renderer*     s_inst;
    static SDL_Renderer* m_renderer;    
    
private:
    
public:
    
    /*
     *  Singleton
     */
    static Renderer* get() { if(!s_inst) s_inst = new Renderer(); return s_inst; }
    
    /*
     *  Initialises the renderer
     */
    static void init(SDL_Renderer* renderer) { m_renderer = renderer; }
    
    // util_functions
    font_t* create_font(const std::string& path, int size);
    
    // drawing functions
    void rect(int x, int y, int w, int h, SDL_Color color);
    void rect_filled(int x, int y, int w, int h, SDL_Color color);
    void string(int x, int y, const std::string& message, font_t* font, SDL_Color color, FontFlags flag = FONTFLAG_SOLID);
    
};

extern Renderer* g_render;
