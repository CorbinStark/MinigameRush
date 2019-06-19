//
//
//                bahamut.h is the graphics library. Include it in all header files
//
//

#include "ENGINE/bahamut.h"

#include "states.h"
#include "menu.h"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#define RENDER_WIDTH 1920.0f
#define RENDER_HEIGHT 1080.0f

int main() {
    printf("\n/////////////////////////////////\n        PROGRAM STARTING\n/////////////////////////////////\n\n");
    bool fullscreen = false;
    bool resizable = true;
    bool renderOnPrimaryMonitor = true;
    init_window(RENDER_WIDTH, RENDER_HEIGHT, "Minigame Rush", fullscreen, resizable, renderOnPrimaryMonitor);
    init_audio();

    set_window_pos(0, 25);
    set_fps_cap(60);
    set_master_volume(100); //0-255
    set_vsync(true);
    set_mouse_state(MOUSE_HIDDEN);
    set_clear_color(BLACK);

    RenderBatch* batch = &create_batch();
    batch->shader = load_default_shader_2D(); //shader is the program that runs on the graphics card for the hardware acceleration. This one is extremely simple, just renders textures onto squares.
    Texture cursor = load_texture("data/art/cursor.png", GL_LINEAR); //loads the cursor.png image into the texture, with a linear interpolation scaling model

    //set uniform projection matrix in the basic shader to project the normal (-1,-1) to (1, 1) coordinate system of OpenGL to a (0, 0) to (RENDER_WIDTH, RENDER_HEIGHT) coordinate system
    //no one needs to understand the specifics of how this works, just accept it for now. You'll need to know how it works if we do 3d though. It involves linear algebra
    start_shader(batch->shader);
    upload_mat4(batch->shader, "projection", orthographic_projection(0, 0, RENDER_WIDTH, RENDER_HEIGHT, -1, 1));
    stop_shader();
    //set_window_size(1360, 768);

    Menu menu = load_menu();

    while(window_open()) {
        //limit the viewport (rendering area) to fit the aspect ratio, this creates black bars on the side of the window if the window is too wide or too high
        Rect view = fit_aspect_ratio(RENDER_WIDTH / RENDER_HEIGHT);
        set_viewport(view.x, view.y, view.width, view.height);
        vec2 mouse = get_mouse_pos(view);

        //prepares screen
        begin_drawing();
        //prepares renderbatch and shader
        begin2D(batch);

        //run menu
        main_menu(&menu, batch, mouse);
        //draw cursor
        draw_texture(batch, cursor, mouse.x, mouse.y);
            
        //flushes renderbatch
        end2D(batch);
        //clears screen
        end_drawing();
    }

    dispose_batch(batch);
    dispose_window();

    return 0;
}
