#include "input.h"

/*
 * input_handle_event
 *
 * Track key press/release events to maintain InputState. This is called once
 * per SDL_Event in the main loop.
 */
void input_handle_event(InputState *state, SDL_Event *ev) {
    if (ev->type == SDL_KEYDOWN) {
        switch (ev->key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
                state->key_up = 1;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                state->key_down = 1;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                state->key_left = 1;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                state->key_right = 1;
                break;
            default:
                break;
        }
    } else if (ev->type == SDL_KEYUP) {
        switch (ev->key.keysym.sym) {
            case SDLK_w:
            case SDLK_UP:
                state->key_up = 0;
                break;
            case SDLK_s:
            case SDLK_DOWN:
                state->key_down = 0;
                break;
            case SDLK_a:
            case SDLK_LEFT:
                state->key_left = 0;
                break;
            case SDLK_d:
            case SDLK_RIGHT:
                state->key_right = 0;
                break;
            default:
                break;
        }
    }
}

/*
 * input_get_movement
 *
 * Compute movement vector based on current key state. Returns deltas that
 * can be applied to a position each frame (e.g., 5 pixels per frame per key).
 */
void input_get_movement(InputState *state, int *dx, int *dy) {
    *dx = 0;
    *dy = 0;

    if (state->key_up) *dy -= 5;
    if (state->key_down) *dy += 5;
    if (state->key_left) *dx -= 5;
    if (state->key_right) *dx += 5;
}
