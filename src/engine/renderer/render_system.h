#ifndef SYSTEMS_RENDER_SYSTEM_H
#define SYSTEMS_RENDER_SYSTEM_H

#include "../graphics/window.h"
#include "../input/input.h"

/*
 * RenderSystemState
 *
 * Tracks the position of the player square and other rendering state.
 * The render system maintains this across frames so position persists.
 */
typedef struct RenderSystemState {
    int square_x;
    int square_y;
} RenderSystemState;

/*
 * render_system_init
 *
 * Purpose: initialize the render system state (square position).
 */
void render_system_init(RenderSystemState *state, int window_width, int window_height);

/*
 * render_system_update
 *
 * Purpose: update entity positions based on input and issue draw calls.
 *
 * This function updates the square position based on input, then draws it.
 * In a full ECS this would query all renderable entities and update them.
 */
void render_system_update(RenderSystemState *state, Window *win, InputState *input);

#endif /* SYSTEMS_RENDER_SYSTEM_H */
