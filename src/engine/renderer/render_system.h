#ifndef SYSTEMS_RENDER_SYSTEM_H
#define SYSTEMS_RENDER_SYSTEM_H

#include "../graphics/window.h"
#include "../graphics/texture.h"
#include "../input/input.h"

/*
 * RenderSystemState
 *
 * Tracks the position of the player square, the background texture, and
 * the current level. The render system maintains this across frames so state persists.
 */
typedef struct RenderSystemState {
    int square_x;
    int square_y;
    Texture background;
    /* Camera top-left in world/background coordinates */
    int camera_x;
    int camera_y;
    /* Current level (0 = onetown, 1 = overworld_level1) */
    int current_level;
} RenderSystemState;

/*
 * render_system_init
 *
 * Purpose: initialize the render system state (square position and load background).
 */
int render_system_init(RenderSystemState *state, Window *win, int window_width, int window_height);

/*
 * render_system_update
 *
 * Purpose: update entity positions based on input and issue draw calls.
 *
 * This function updates the square position based on input, then draws the
 * background texture and the square on top.
 */
void render_system_update(RenderSystemState *state, Window *win, InputState *input);

/*
 * render_system_destroy
 *
 * Purpose: clean up resources (background texture).
 */
void render_system_destroy(RenderSystemState *state);

/*
 * load_level
 *
 * Purpose: internal helper to load a new background and reposition the player.
 *
 * Unloads the current background and loads a new one at the specified path,
 * then positions the player at the given coordinates.
 */
int load_level(RenderSystemState *state, Window *win, const char *bg_path, int player_x, int player_y);

#endif /* SYSTEMS_RENDER_SYSTEM_H */
