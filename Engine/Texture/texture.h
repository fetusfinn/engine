/*
 *  texture.h
 */
#pragma once

#include "global.h"
#include "filesystem.h"
#include "vec2.h"

class Texture
{
private:
    
    static SDL_Renderer* s_renderer;
    
    SDL_Texture* m_texture;
    
private:
    
    void render(SDL_Rect dst, float rotation = 0, SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
public:
    
    static void init(SDL_Renderer* renderer);
    static Texture* load_from_image(const std::string& img_path);
    
    Texture(SDL_Texture* texture);
    ~Texture();
    
    void render(int x, int y, float rotation = 0, SDL_Rect* clip = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
    
    // getters
    vec2 get_size();
    SDL_Texture* get_raw() { return m_texture; }
    
};
