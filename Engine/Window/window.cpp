/*      window.cpp
 *
 *
 *
 */
#include "window.h"

Window* Window::s_inst;

Window::Window(const std::string& title, vec2 size)
{
    m_title = title;
    m_size  = size;
    m_background_tex = nullptr;
    
    m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_size.x, m_size.y, SDL_WINDOW_SHOWN);
}

Window::~Window()
{
    this->destroy();
}

/*
 *
 *
 */
Window* Window::init(const std::string& title, vec2 size)
{
    s_inst = new Window(title, size);
    return s_inst;
}

/*
 *  set_background
 *  Loads the background texture
 */
void Window::set_background(const std::string& path)
{
    m_background_tex = Texture::load_from_image(path);
}

/*
 *  on_render
 *  Renders all window related textures
 */
void Window::on_render()
{
    if(!m_background_tex)
        return;
    
    static vec2  tex_size = m_background_tex->get_size();    
    static float num_x = m_size.x / tex_size.x;
    static float num_y = m_size.y / tex_size.y;
    
    for(int x = 0; x < num_x; x++)
    {
        for(int y = 0; y < num_y; y++)
        {
            m_background_tex->render(x * tex_size.x, y * tex_size.y);
        }
    }
}
