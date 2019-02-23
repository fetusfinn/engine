/*
 *  tilemap.h
 */
#pragma once

#include "global.h"
#include "texture.h"

class Tilemap
{
private:
    
    static vec2             tile_size;
    
    Texture*                m_texture;
    std::vector<SDL_Rect>   m_clips;
    
private:
    
    void load(const std::string& path);
    
public:
    
    Tilemap(const std::string& path);
    ~Tilemap();
    
    void render(int x, int y, int clip, float rotation = 0.f);
    
    // setters
    void set_tile_size(vec2 size) { tile_size = size; }
    
    // getters
    vec2 get_tile_size() { vec2 tmp = tile_size; return tmp; }
};
