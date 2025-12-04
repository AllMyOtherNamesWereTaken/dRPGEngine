#include "window.h"
#include <stdio.h>

/*
 * Initialize SDL, create the SDL_Window and SDL_Renderer, and store them in
 * the provided Window struct.
 *
 * Why: centralizes platform setup so callers only need to call a single
 * function to get a working rendering context. On error the function prints
 * a diagnostic to stderr, cleans up, and returns non-zero.
 */
int window_init(Window *win, const char *title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return -1;
    }

    win->sdl_window = SDL_CreateWindow(title,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       width, height,
                                       SDL_WINDOW_SHOWN);
    if (!win->sdl_window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    /* Create a hardware-accelerated renderer with vsync enabled. */
    win->renderer = SDL_CreateRenderer(win->sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!win->renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win->sdl_window);
        SDL_Quit();
        return -1;
    }

    /* Cache the logical size for convenience. */
    win->width = width;
    win->height = height;
    return 0;
}


/*
 * Poll SDL events and set the quit flag when the user requests exit.
 *
 * Why: Event polling must happen regularly to keep the OS window responsive.
 * This function is intentionally minimal: it detects window close and Escape
 * key and is a single place to extend event handling or forward events into
 * an input system.
 */
void window_poll_events(Window *win, int *should_quit) {
    (void)win; /* unused now but kept for future per-window handling */
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        if (ev.type == SDL_QUIT) {
            *should_quit = 1;
        } else if (ev.type == SDL_KEYDOWN) {
            if (ev.key.keysym.sym == SDLK_ESCAPE) {
                *should_quit = 1;
            }
        }
    }
}


/*
 * Clear the renderer to the chosen background color.
 *
 * Why: A fresh frame should start from a known background. This simple
 * function wraps the SDL calls so callers don't need to include SDL directly.
 */
void window_clear(Window *win) {
    /* Default background: white */
    SDL_SetRenderDrawColor(win->renderer, 255, 255, 255, 255);
    SDL_RenderClear(win->renderer);
}


/*
 * Draw a filled rectangle using the renderer.
 *
 * Why: Small primitive useful for debugging or for simple UI until a sprite
 * system exists. This function translates engine coordinates directly to the
 * SDL renderer; batching or texture drawing would live elsewhere in the
 * engine once added.
 */
void window_draw_rect(Window *win, int x, int y, int w, int h, SDL_Color color) {
    SDL_Rect r = { x, y, w, h };
    SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(win->renderer, &r);
}


/*
 * Present the current backbuffer to the screen.
 *
 * Why: Separates accumulation of draw calls from the actual buffer swap.
 */
void window_present(Window *win) {
    SDL_RenderPresent(win->renderer);
}


/*
 * Draw a texture to the screen.
 *
 * Why: Simple wrapper to render a preloaded texture to a destination rectangle.
 */
void window_draw_texture(Window *win, SDL_Texture *texture, SDL_Rect *dest) {
    SDL_RenderCopy(win->renderer, texture, NULL, dest);
}


/*
 * Destroy renderer and window and call SDL_Quit().
 *
 * Why: Provides a single, safe place for SDL cleanup. If you add other SDL
 * subsystems (audio, ttf), destroy those before calling this or extend this
 * function to clean them up.
 */
void window_destroy(Window *win) {
    if (win->renderer) SDL_DestroyRenderer(win->renderer);
    if (win->sdl_window) SDL_DestroyWindow(win->sdl_window);
    SDL_Quit();
}
