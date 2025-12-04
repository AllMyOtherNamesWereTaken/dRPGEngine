#include "render_system.h"
#include <stdio.h>

/*
 * render_system_init
 *
 * Initialize the render system state (position the square in the center and
 * load the background texture).
 */
int render_system_init(RenderSystemState *state, Window *win, int window_width, int window_height) {
    state->square_x = (window_width - 50) / 2;
    state->square_y = (window_height - 50) / 2;

    if (texture_load_png(&state->background, win->renderer, "src/game/assets/background.png") != 0) {
        fprintf(stderr, "Failed to load background texture\n");
        return -1;
    }
    return 0;
}

/*
 * render_system_update
 *
 * Update the square position based on input, draw the background texture,
 * then draw the square on top.
 *
 * Why: demonstrates input integration with rendering. The system reads
 * input state, updates entity positions, and issues draw calls.
 * In a real ECS this would iterate all entities with Update/Render components.
 */
void render_system_update(RenderSystemState *state, Window *win, InputState *input) {
    int dx, dy;
    input_get_movement(input, &dx, &dy);

    /* Update position (with simple bounds checking) */
    state->square_x += dx;
    state->square_y += dy;

    if (state->square_x < 0) state->square_x = 0;
    if (state->square_y < 0) state->square_y = 0;
    if (state->square_x + 50 > win->width) state->square_x = win->width - 50;
    if (state->square_y + 50 > win->height) state->square_y = win->height - 50;

    /* Draw the background texture stretched to fill the window */
    SDL_Rect bg_rect = { 0, 0, win->width, win->height };
    window_draw_texture(win, state->background.sdl_texture, &bg_rect);

    /* Draw the green square on top */
    SDL_Color green = { 0, 255, 0, 255 };
    window_draw_rect(win, state->square_x, state->square_y, 50, 50, green);
}

/*
 * render_system_destroy
 *
 * Clean up the background texture.
 */
void render_system_destroy(RenderSystemState *state) {
    texture_destroy(&state->background);
}
