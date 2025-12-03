#include "engine/graphics/window.h"
#include "systems/render_system.h"

/*
 * main
 *
 * Responsibilities:
 *  - Initialize engine/platform resources (the Window).
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

    int quit = 0;
    while (!quit) {
        /* Poll platform events and update quit flag */
        window_poll_events(&win, &quit);

        /* Start a new frame */
        window_clear(&win);

        /* Run render system which issues draw calls */
        render_system_update(&win);

        /* Present the composed frame to the screen */
        window_present(&win);

        /* Simple frame-cap: sleep ~16ms to aim for ~60 FPS. Replace with
         * a delta-time based scheduler in real projects. */
        SDL_Delay(16);
    }

    /* Clean up engine/platform resources */
    window_destroy(&win);
    return 0;
}