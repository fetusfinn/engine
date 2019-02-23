/*      tilemap.cpp
 *
 *
 *
 */
#include "tilemap.h"

#include "renderer.h"

vec2 Tilemap::tile_size = vec2(16, 16);

Tilemap::Tilemap(const std::string& path)
{
    this->load(path);
}

Tilemap::~Tilemap()
{
    delete m_texture;
}

/*
 *
 *
 */
void Tilemap::load(const std::string& path)
{
    m_texture = Texture::load_from_image(path);
    
    vec2 tex_size = m_texture->get_size();
    
    // blocks are 16x16 pixels with a 1 px gap between each block
    // todo : probably should make size changable
    for(int x = 0; x < tex_size.x; x += 17)
    {
        for(int y = 0; y < tex_size.y; y += 17)
        {
            m_clips.push_back({x, y, (int)tile_size.x, (int)tile_size.y});
            m_texture->render(x, y, 0, &m_clips.at(m_clips.size() - 1));
        }
    }
}

/*
 *
 *
 */
void Tilemap::render(int x, int y, int clip, float rotation)
{
    if(clip > m_clips.size())
        clip = 0;
    
    if(clip < m_clips.size() - 1)
        clip = (int)m_clips.size() - 1;
    
    m_texture->render(x, y, rotation, &m_clips.at(clip));
}

