/*
 *  sprite.h
 */
#pragma once

#include <unordered_map>

#include "global.h"
#include "texture.h"
#include "util.h"
#include "math.h"

/*
 *  Animation
 *  An animation is just a list of sprites that are played in succession, so we just need to store the indices of the sprites that we want to play in order
 */
typedef std::vector<int> Animation;

// todo : move
#define ANIM_WALK "walk"
#define ANIM_IDLE "idle"
#define ANIM_RUN  "run"

class Sprite
{
private:
    
    Texture*                m_texture;
    std::vector<SDL_Rect>   m_clips;
    SDL_RendererFlip        m_flip;
    vec2                    m_sprite_size;
    int                     m_last_anim_index;
    timestamp_t             m_last_anim_update;
    
    // map of all animations
    std::unordered_map<std::string, Animation> m_animations;
    
public:
    
    Sprite(const std::string& path, int num_sprites);
    ~Sprite();
    
    // maybe rename to add_animation
    void push_back_animation(std::string anim_name, Animation anim_clips);
    void push_back_animation(std::string anim_name, int first, int last);
    
    void animate(vec2 pos, std::string anim_name, int start_anim = -1, float rotation = 0.f);
    
    // setters
    void set_flip(SDL_RendererFlip flip) { m_flip = flip; }
    
    // getters
    Texture* get_texture() { return this->m_texture; }
    vec2 get_sprite_size() { return this->m_sprite_size; }
    
};
