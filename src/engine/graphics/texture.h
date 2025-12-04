#ifndef ENGINE_GRAPHICS_TEXTURE_H
#define ENGINE_GRAPHICS_TEXTURE_H

#include <SDL2/SDL.h>

/*
 * Texture
 *
 * Simple wrapper for an SDL_Texture with dimension info. The renderer owns
 * this and is responsible for destroying it.
 */
typedef struct Texture {
    SDL_Texture *sdl_texture;
    int width;
    int height;
} Texture;

/*
 * texture_load_png
 *
 * Purpose: load a PNG file and create an SDL_Texture from it.
 *
 * Returns 0 on success, non-zero on failure. On success the texture struct
 * is populated with the loaded texture and dimensions. The caller must call
 * texture_destroy() to clean up.
 */
int texture_load_png(Texture *tex, SDL_Renderer *renderer, const char *path);

/*
 * texture_destroy
 *
 * Purpose: free the SDL_Texture.
 */
void texture_destroy(Texture *tex);

#endif /* ENGINE_GRAPHICS_TEXTURE_H */
