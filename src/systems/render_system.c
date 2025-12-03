#include "render_system.h"

/*
 * render_system_update
 *
 * Minimal example render system.
 *
 * Why: demonstrates how a system calls into the engine's rendering API.
 * In a real ECS this function would:
 *  - query entities with Render/Transform components,
 *  - compute their screen positions using camera and transform data,
 *  - issue draw calls (sprites, text, shapes) through engine functions,
 *  - optionally sort by depth or layer before drawing.
 *
 * Here we draw a single blue rectangle as a placeholder for sprite output.
 */
void render_system_update(Window *win) {
    SDL_Color blue = { 0, 120, 200, 255 };
    window_draw_rect(win, 100, 100, 200, 40, blue);
}
