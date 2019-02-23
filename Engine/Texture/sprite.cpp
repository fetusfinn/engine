/*      sprite.cpp
 *
 *  todo : clean up
 *
 */
#include "sprite.h"

/*
 *  constructor
 *  Loads the sprite sheet then saves all sprite clips into a vector
 *  Note : sprite sheets should have the sprites one ontop of another each equaly spaced
 */
Sprite::Sprite(const std::string& path, int num_sprites)
{
    m_texture = Texture::load_from_image(path);
    
    vec2 tex_size = m_texture->get_size();
    
    int w = tex_size.x;
    int h = tex_size.y / num_sprites;
    
    for(int y = 0; y < num_sprites; y++)
    {
        SDL_Rect clip;
        
        // just easier to read
        clip.x = 0;
        clip.y = y * h;
        clip.w = w;
        clip.h = h;
        
        m_clips.push_back(clip);
    }
    
    m_sprite_size       = vec2(w, h);
    m_last_anim_index   = 0;
    m_last_anim_update  = timestamp();
}

/*
 *
 */
Sprite::~Sprite()
{
    delete m_texture;
}

/*
 *  push_back_animation
 *  Saves an animation to a std::vector
 */
void Sprite::push_back_animation(std::string anim_name, Animation anim_clips)
{
    insert_into_map(m_animations, anim_name, anim_clips);
}

/*
 *  push_back_animation
 *  Saves indices of sprites between first and last into a std::vector
 */
void Sprite::push_back_animation(std::string anim_name, int first, int last)
{
    if(last > m_clips.size())
        last = (int)m_clips.size() - 1;
    
    std::vector<int> clips;
    for(int i = first; i < last; i++)
        clips.push_back(i);
    
    this->push_back_animation(anim_name, clips);
}

/*
 *  animate
 *  Animates the sprite with the given animation
 */
void Sprite::animate(vec2 pos, std::string anim_name, int anim_start, float rotation)
{
    Animation anim = get_from_map(m_animations, anim_name);
    
    if(anim.empty())
        return;
    
    static Animation last_anim = anim;
    int last_index = (last_anim == anim ? m_last_anim_index : 0);
    auto time_since_last_update = timestamp() - m_last_anim_update;
    
    // limit the number of anim updates per sec
    if(time_since_last_update < 20)
    {
        m_texture->render(pos.x, pos.y, rotation, &m_clips.at(anim.at(last_index)), m_flip);
        return;
    }
    
    const int time_before_reset = 100;
    
    // if there were more than time_before_reset between anims then restart anim
    if((time_since_last_update > time_before_reset) && anim_start == -1)
        anim_start = 0;
    
    // if it was less than time_before_reset and we werent given a specified anim then draw the next anim
    else if(anim_start == -1)
        anim_start = last_index + 1;
    
    // else we just use the given start index
    
    // clamp
    if(anim_start < 0 || anim_start >= anim.size())
        anim_start = 0;
    
    // get the clip for the correct anim
    SDL_Rect* anim_clip = &m_clips.at(anim.at(anim_start));
    
    // draw sprite
    m_texture->render(pos.x, pos.y, rotation, anim_clip, m_flip);
    
    // if we were'nt idle then
    if(anim_name != ANIM_IDLE)
    {
        last_anim = anim;
        m_last_anim_index = anim_start;
        m_last_anim_update = timestamp();
    }
}
