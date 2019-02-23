/*      renderer.cpp
 *
 *
 *
 */
#include "renderer.h"

Renderer*       g_render                = nullptr;
Renderer*       Renderer::s_inst        = nullptr;
SDL_Renderer* 	Renderer::m_renderer    = nullptr;

// todo : maybe move elsewhere
namespace Fonts
{
    font_t* small;
    font_t* large;
    
    /*
     *  init
     *  Creates all fonts
     */
    void init()
    {
        small = g_render->create_font("small", 12);                
        large = g_render->create_font("large", 15);
    }

    /*
     *  destroy
     *  Destroys all fonts
     */
    void destroy()
    {
        TTF_CloseFont(small);
        TTF_CloseFont(large);
    }
}

/*
 *  create_font
 *  Imports a font from a file
 */
font_t* Renderer::create_font(const std::string& font, int size)
{
    return TTF_OpenFont(std::string(ASSETS_FONTS + font + ".ttf").c_str(), size);
}

/*
 *  rect
 *  Draws a hollow rectangle to the screen
 */
void Renderer::rect(int x, int y, int w, int h, SDL_Color color)
{
    SDL_Rect r = {x, y, w, h};
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(m_renderer, &r);    
}

/*
 *  rect_filled
 *  Draws a filled rectangle to the screen
 */
void Renderer::rect_filled(int x, int y, int w, int h, SDL_Color color)
{
    SDL_Rect r = {x, y, w, h};
    SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(m_renderer, &r);
}

/*
 *  string
 *  Draws a string to the screen
 */
void Renderer::string(int x, int y, const std::string& message, font_t* font, SDL_Color color, FontFlags flag)
{
    if(!font)
    {
        error("font == nullptr");
        return;
    }
    
    SDL_Surface* surf = nullptr;
    
    if(flag == FONTFLAG_SHADED)
        surf = TTF_RenderText_Shaded(font, message.c_str(), color, {0, 0, 0, 0});
    
    else if(flag == FONTFLAG_BLENDED)
        surf = TTF_RenderText_Blended(font, message.c_str(), color);
    
    else // FONTFLAG_SOLID
        surf = TTF_RenderText_Solid(font, message.c_str(), color);
 
    if(!surf)
    {
        print_sdl_error("TTF_RenderText");
        return;
    }
    
    Texture* tex = new Texture(SDL_CreateTextureFromSurface(m_renderer, surf));
    
    if(!tex)
        print_sdl_error("SDL_CreateTextureFromSurface");
    
    // clean up
    SDL_FreeSurface(surf);
    
    tex->render(x, y);
    
    delete tex;
}
