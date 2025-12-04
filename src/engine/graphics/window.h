#ifndef ENGINE_GRAPHICS_WINDOW_H
#define ENGINE_GRAPHICS_WINDOW_H

#include <SDL2/SDL.h>

/**
 * Window
 *
 * Engine-owned wrapper for SDL window/renderer resources. Systems receive a
 * pointer to this struct but do not own the pointers; creation and destruction
 * are handled by the engine via the functions below.
 */
typedef struct Window {
    SDL_Window *sdl_window;   /* native SDL window handle */
    SDL_Renderer *renderer;   /* SDL renderer used for 2D draw calls */
    int width;                /* cached width in pixels */
    int height;               /* cached height in pixels */
} Window;


/*
 * Initialize SDL and create a window + renderer.
 *
 * Purpose: perform all platform initialization required for rendering and
 * provide a simple renderer-backed `Window` object to the rest of the engine.
 * Returns 0 on success, non-zero on failure. On failure the function will
 * clean up any partially created SDL resources.
 */
int window_init(Window *win, const char *title, int width, int height);


/*
 * Poll platform events and update quit flag.
 *
 * Purpose: centralize OS event polling (window close, keyboard) so the main
 * loop or higher-level input system can act on user requests. The function
 * sets `*should_quit` to non-zero when the user requests quit (close button
 * or Escape key in the current implementation).
 */
void window_poll_events(Window *win, int *should_quit);


/*
 * Clear the current render target.
 *
 * Purpose: reset the frame to a known background color before issuing draw
 * calls. This implementation clears to white; the color can be parameterized
 * later if needed.
 */
void window_clear(Window *win);


/*
 * Draw a filled rectangle.
 *
 * Purpose: a small primitive useful for placeholders, debugging, and simple
 * UI. Coordinates are in window pixels. Systems will typically call higher
 * level sprite/texture APIs instead of raw rectangles in a finished engine.
 */
void window_draw_rect(Window *win, int x, int y, int w, int h, SDL_Color color);


/*
 * Present the current frame.
 *
 * Purpose: swap the back buffer to the screen after all draw calls for the
 * frame have completed. Separating draw and present lets systems issue many
 * draw operations before a single buffer swap.
 */
void window_present(Window *win);


/*
 * Draw a texture stretched to fill a rectangle.
 *
 * Purpose: render a preloaded texture to the screen. Useful for backgrounds,
 * sprites, and UI elements.
 */
void window_draw_texture(Window *win, SDL_Texture *texture, SDL_Rect *dest);


/*
 * Destroy the window and shut down SDL.
 *
 * Purpose: free renderer and window resources and call `SDL_Quit()` to leave
 * the SDL subsystem in a clean state. This is the single place for SDL
 * shutdown in this minimal engine.
 */
void window_destroy(Window *win);

#endif /* ENGINE_GRAPHICS_WINDOW_H */
