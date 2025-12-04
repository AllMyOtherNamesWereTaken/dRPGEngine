#include "engine/graphics/window.h"
#include "engine/renderer/render_system.h"
#include "engine/input/input.h"

/*
 * main
 *
 * Responsibilities:
 *  - Initialize engine/platform resources (the Window, input state, render system).
 *  - Run the main loop: poll events, update systems, render, present.
 *  - Clean up resources on exit.
 *
 * Note: In a more complete engine the main loop would also step the ECS
 * world (system scheduling), run a fixed-step simulation or variable-step
 * updates, and forward input events into an input system.
 */
int main(void) {
    Window win;
    if (window_init(&win, "RPG", 500, 500) != 0) {
        return 1;
    }

    InputState input = {0};
    RenderSystemState render_state;
    if (render_system_init(&render_state, &win, win.width, win.height) != 0) {
        window_destroy(&win);
        return 1;
    }

    int quit = 0;
    SDL_Event event;
    while (!quit) {
        /* Poll platform events and update quit flag and input state */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = 1;
            }
            input_handle_event(&input, &event);
        }

        /* Start a new frame */
        window_clear(&win);

        /* Run render system which updates positions and issues draw calls */
        render_system_update(&render_state, &win, &input);

        /* Present the composed frame to the screen */
        window_present(&win);

        /* Simple frame-cap: sleep ~16ms to aim for ~60 FPS. Replace with
         * a delta-time based scheduler in real projects. */
        SDL_Delay(16);
    }

    /* Clean up resources */
    render_system_destroy(&render_state);
    window_destroy(&win);
    return 0;
}
