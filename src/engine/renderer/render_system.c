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
    state->camera_x = 0;
    state->camera_y = 0;
    state->current_level = 0; /* Start at onetown */

    if (texture_load_png(&state->background, win->renderer, "src/game/assets/onetown.png") != 0) {
        fprintf(stderr, "Failed to load background texture\n");
        return -1;
    }
    /* Position camera to center on the square initially */
    int cam_x = state->square_x + 25 - (window_width / 2);
    int cam_y = state->square_y + 25 - (window_height / 2);
    if (cam_x < 0) cam_x = 0;
    if (cam_y < 0) cam_y = 0;
    /* Clamp to background bounds if larger than the window */
    if (state->background.width > window_width) {
        int max_cx = state->background.width - window_width;
        if (cam_x > max_cx) cam_x = max_cx;
    } else {
        cam_x = 0;
    }
    if (state->background.height > window_height) {
        int max_cy = state->background.height - window_height;
        if (cam_y > max_cy) cam_y = max_cy;
    } else {
        cam_y = 0;
    }
    state->camera_x = cam_x;
    state->camera_y = cam_y;
    return 0;
}

/*
 * load_level
 *
 * Helper to load a new level background and reposition the player.
 * Unloads the old texture and loads the new one.
 */
int load_level(RenderSystemState *state, Window *win, const char *bg_path, int player_x, int player_y) {
    texture_destroy(&state->background);
    if (texture_load_png(&state->background, win->renderer, bg_path) != 0) {
        fprintf(stderr, "Failed to load level texture: %s\n", bg_path);
        return -1;
    }
    state->square_x = player_x;
    state->square_y = player_y;
    state->camera_x = 0;
    state->camera_y = 0;
    return 0;
}


/*
 * render_system_update
 *
 * Update the square position based on input, check for level transitions,
 * draw the background texture, then draw the square on top.
 *
 * Why: demonstrates input integration with rendering and level transitions.
 * The system reads input state, updates entity positions, detects transitions,
 * and issues draw calls.
 */
void render_system_update(RenderSystemState *state, Window *win, InputState *input) {
    int dx, dy;
    input_get_movement(input, &dx, &dy);

    /* Update position (with simple bounds checking) */
    state->square_x += dx;
    state->square_y += dy;

    /* Clamp square to background/world bounds */
    if (state->square_x < 0) state->square_x = 0;
    if (state->square_y < 0) state->square_y = 0;
    if (state->square_x + 50 > state->background.width) state->square_x = state->background.width - 50;
    if (state->square_y + 50 > state->background.height) state->square_y = state->background.height - 50;

    /* Check for level transitions */
    if (state->current_level == 0) {
        /* On onetown: transition to overworld_level1 when hitting top or bottom edge */
        if (state->square_y <= 0) {
            /* Hit top edge of onetown, load overworld_level1 with player at specified position */
            if (load_level(state, win, "src/game/assets/overworld_level1.png", 1800, 1180) == 0) {
                state->current_level = 1;
            }
        } else if (state->square_y + 50 >= state->background.height) {
            /* Hit bottom edge of onetown, load overworld_level1 with player at specified position */
            if (load_level(state, win, "src/game/assets/overworld_level1.png", 1800, 1180) == 0) {
                state->current_level = 1;
            }
        }
    } else if (state->current_level == 1) {
        /* On overworld_level1: transition back to onetown when at exit location */
        if (state->square_x >= 1745 - 25 && state->square_x <= 1745 + 25 &&
            state->square_y >= 1177 - 25 && state->square_y <= 1177 + 25) {
            /* Player is near the exit point, load onetown */
            if (load_level(state, win, "src/game/assets/onetown.png", 
                          (500 - 50) / 2, (500 - 50) / 2) == 0) {
                state->current_level = 0;
            }
        }
    }

    /* Compute camera so the square is near the center of the view */
    int cam_x = state->square_x + 25 - (win->width / 2);
    int cam_y = state->square_y + 25 - (win->height / 2);
    if (cam_x < 0) cam_x = 0;
    if (cam_y < 0) cam_y = 0;
    if (state->background.width > win->width) {
        int max_cx = state->background.width - win->width;
        if (cam_x > max_cx) cam_x = max_cx;
    } else {
        cam_x = 0;
    }
    if (state->background.height > win->height) {
        int max_cy = state->background.height - win->height;
        if (cam_y > max_cy) cam_y = max_cy;
    } else {
        cam_y = 0;
    }
    state->camera_x = cam_x;
    state->camera_y = cam_y;

    /* Prepare source rect from the background texture. If the texture is
     * smaller than the window, use the full texture as the source and
     * stretch it to the window. Otherwise copy the window-sized region
     * starting at the camera position. */
    SDL_Rect src;
    SDL_Rect dest = {0, 0, win->width, win->height};
    if (state->background.width >= win->width) {
        src.x = state->camera_x;
        src.w = win->width;
    } else {
        src.x = 0;
        src.w = state->background.width;
    }
    if (state->background.height >= win->height) {
        src.y = state->camera_y;
        src.h = win->height;
    } else {
        src.y = 0;
        src.h = state->background.height;
    }

    /* Draw background region scaled to the window */
    SDL_RenderCopy(win->renderer, state->background.sdl_texture, &src, &dest);

    /* Compute on-screen position for the square (world -> screen) */
    int screen_x = state->square_x - state->camera_x;
    int screen_y = state->square_y - state->camera_y;
    SDL_Color green = { 0, 255, 0, 255 };
    window_draw_rect(win, screen_x, screen_y, 50, 50, green);
}

/*
 * render_system_destroy
 *
 * Clean up the background texture.
 */
void render_system_destroy(RenderSystemState *state) {
    texture_destroy(&state->background);
}
