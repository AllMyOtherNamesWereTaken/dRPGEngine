#include "texture.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>

/*
 * texture_load_png
 *
 * Load a PNG from disk using SDL_image and create an SDL_Texture.
 *
 * Why: centralizes image loading so the rest of the engine doesn't need to
 * know about SDL_image or surface handling.
 */
int texture_load_png(Texture *tex, SDL_Renderer *renderer, const char *path) {
    SDL_Surface *surface = IMG_Load(path);
    if (!surface) {
        fprintf(stderr, "IMG_Load Error: %s\n", IMG_GetError());
        return -1;
    }

    tex->sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!tex->sdl_texture) {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return -1;
    }

    tex->width = surface->w;
    tex->height = surface->h;
    SDL_FreeSurface(surface);
    return 0;
}

/*
 * texture_destroy
 *
 * Free the SDL_Texture. Safe to call on a texture that failed to load
 * (it will be NULL and the check skips destruction).
 */
void texture_destroy(Texture *tex) {
    if (tex->sdl_texture) {
        SDL_DestroyTexture(tex->sdl_texture);
        tex->sdl_texture = NULL;
    }
}
