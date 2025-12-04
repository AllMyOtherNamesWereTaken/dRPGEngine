#ifndef SYSTEMS_RENDER_SYSTEM_H
#define SYSTEMS_RENDER_SYSTEM_H

#include "../graphics/window.h"
#include "../graphics/texture.h"
#include "../input/input.h"

/*
 * RenderSystemState
 *
 * Tracks the position of the player square and the background texture.
 * The render system maintains this across frames so position persists.
 */
typedef struct RenderSystemState {
    int square_x;
    int square_y;
    Texture background;
    /* Camera top-left in world/background coordinates */
    int camera_x;
    int camera_y;
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

#endif /* SYSTEMS_RENDER_SYSTEM_H */
