/*      main.cpp
 *
 *
 *
 */
#include "Engine/global.h"
#include "engine.h"

int main(int argc, const char* argv[])
{
    if(argc > 1 && !strcmp(argv[1], "-d"))
        sleep(60);
    
    Engine* engine = Engine::get();
    
    if(engine->init())
    {
        engine->run();
    }
    
    engine->shutdown();
    
    return 0;
}

/*
 *  Todo (in order)
 *
 *  - Base engine class
 *      - Build up more later
 *
 *  - Texture class
 *
 *  - Util
 *      - Math, vectors, filesystem -> file funcs, definitions
 *
 *  - Window class
 *
 *  - Entity
 *
 *  - Renderer class
 *      - Use ImGui to render
 *          - Use own renderer
 *      - Draw shapes and text
 *      - void draw_texture(), pretty much same as Texture::draw
 *      - m_draw_list -> i know what to do
 *      - colour class
 *
 *  - Clean up code
 *
 *
 *
 *  Todo later
 *
 *  - ImGui
 *
 *  - Camera
 *
 *  - Hot loading  -> can do later, but the earlier the better
 *  - Event system -> can do later
 *
 *
 *
 *  Notes
 *
 *  - Save all strings into a file so they can be changed easily between projects
 *  - http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
