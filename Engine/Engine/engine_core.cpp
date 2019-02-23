/*      engine_core.cpp
 *
 *  Core engine functions that shouldn't need to be changed once completely finished
 *
 *
 *
 */
#include "engine.h"

int g_tick = 0;

Engine* Engine::s_inst = nullptr;

/*
 *  init
 *  Initialises the core engine and modules
 */
bool Engine::init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        print_sdl_error("SDL_Init");
        return false;
    }
    
    sdl_init = true;
    
    if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        print_sdl_error("IMG_Init");
        shutdown();
        return false;
    }
    
    img_init = true;
    
    if(TTF_Init())
    {
        print_sdl_error("TTF_Init");
        shutdown();
        return false;
    }
    
    ttf_init = true;
    
    m_window = Window::init(WINDOW_TITLE, WINDOW_SIZE);
    
    if(!m_window->is_valid())
    {
        print_sdl_error("SDL_CreateWindow");
        shutdown();
        return false;
    }
    
    m_renderer = SDL_CreateRenderer(m_window->get_window(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if(!m_renderer)
    {
        print_sdl_error("SDL_CreateRenderer");
        shutdown();
        return false;
    }
    
    Texture::init(m_renderer);
    Renderer::init(m_renderer);
    
    g_render = Renderer::get();
    
    Fonts::init();
    
    this->m_speed = 10;
    this->on_init();
    
    return true;
}

/*
 *  run
 *  Runs the application
 */
void Engine::run()
{
    this->tick = 0;
    this->running = true;        
    
    for(;this->running; this->tick++)
    {
        g_tick = this->tick;
        
        // start rendering
        SDL_RenderClear(m_renderer);
        {
            // render background
            m_window->on_render();
            
            this->on_render();
            
            g_render->string(10, 10, std::to_string(m_fps.m_fps), Fonts::large, SDL_COLOR_WHITE);
        }
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
        SDL_RenderPresent(m_renderer);
        // finish rendering
        
        handle_events();
        
        this->update();
        
        SDL_Delay(10);
    }
}

/*
 *  shutdown
 *  Destroys all objects
 */
void Engine::shutdown()
{
    this->on_shutdown();
    
    Fonts::destroy();
    
    delete g_render;
    
    if(m_renderer)
        SDL_DestroyRenderer(m_renderer);
    
    if(m_window->is_valid())
    {
        m_window->destroy();
        delete m_window;
    }
    
    if(img_init)
        IMG_Quit();
    
    if(ttf_init)
        TTF_Quit();
    
    if(sdl_init)
        SDL_Quit();
}

/*
 *  handle_events
 *
 */
void Engine::handle_events()
{
    static uint8_t* keyboard_state = nullptr;
    
    if(!keyboard_state)
        keyboard_state = (uint8_t*)SDL_GetKeyboardState(nullptr);
    
    SDL_Event* event = new SDL_Event;
    
    while (SDL_PollEvent(event))
    {
        if(event->type == SDL_QUIT)
        {
            this->quit();
            break;
        }
        
        /*
         *  Let the game handle its events
         */
        this->on_event(event, keyboard_state);
    }
    
    delete event;
}

/*
 *
 *
 */
void Engine::update()
{
    this->on_update();
    
    m_fps.on_update();
}
