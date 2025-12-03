#ifndef ENGINE_INPUT_INPUT_H
#define ENGINE_INPUT_INPUT_H

#include <SDL2/SDL.h>

/*
 * InputState
 *
 * Tracks the current state of keyboard input. Systems query this to determine
 * how to update entities (e.g., player movement). Updated each frame by
 * input_handle_event().
 */
typedef struct InputState {
    int key_up;
    int key_down;
    int key_left;
    int key_right;
} InputState;

/*
 * input_handle_event
 *
 * Purpose: update InputState based on SDL events.
 *
 * Call this for each SDL_Event in the main loop so the input system can track
 * which keys are currently pressed. The system maintains state across frames.
 */
void input_handle_event(InputState *state, SDL_Event *ev);

/*
 * input_get_movement
 *
 * Purpose: compute movement delta based on current key state.
 *
 * Returns the x and y movement amount (e.g., -5 to 5 pixels per frame) based
 * on which keys are pressed. WASD and arrow keys are supported.
 */
void input_get_movement(InputState *state, int *dx, int *dy);

#endif /* ENGINE_INPUT_INPUT_H */
