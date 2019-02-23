/*      texture.cpp
 *
 *
 *
 */
#include "texture.h"

SDL_Renderer* Texture::s_renderer;

Texture::Texture(SDL_Texture* texture)
{
    this->m_texture = texture;
}

Texture::~Texture()
{
    SDL_DestroyTexture(m_texture);
}

/*
 *  init
 *  Initialises the renderer
 */
void Texture::init(SDL_Renderer* renderer)
{
    s_renderer = renderer;
}

/*
 *  load_from_image
 *  Loads an image into a texture
 */
Texture* Texture::load_from_image(const std::string& img_path)
{
    SDL_Texture* tex = IMG_LoadTexture(s_renderer, img_path.c_str());
    
    if(!tex)
        print_sdl_error("IMG_LoadTexture");
    
    Texture* ret = new Texture(tex);
    
    return ret;
}

/*
 *  render
 *  Renders the texture to the screen
 */
void Texture::render(SDL_Rect dst, float rotation, SDL_Rect* clip, SDL_RendererFlip flip)
{
    if(!this->m_texture)
    {
        error("m_texture == nullptr");
        return;
    }
    
    SDL_RenderCopyEx(s_renderer, m_texture, clip, &dst, rotation, NULL, flip);
}

/*
 *  render
 *  Renders the texture to the screen
 */
void Texture::render(int x, int y, float rotation, SDL_Rect* clip, SDL_RendererFlip flip)
{
    if(!this->m_texture)
    {
        error("m_texture == nullptr");
        return;
    }
    
    SDL_Rect dst = {x, y};
    
    if (clip)
    {
        dst.w = clip->w;
        dst.h = clip->h;
    }
    else
    {
        SDL_QueryTexture(m_texture, NULL, NULL, &dst.w, &dst.h);
    }
    
    this->render(dst, rotation, clip, flip);
}

/*
 *  get_size
 *  Returns the size of the texture
 */
vec2 Texture::get_size()
{
    int w, h;
    SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
    return vec2(w, h);
}
