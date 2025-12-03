#ifndef SYSTEMS_RENDER_SYSTEM_H
#define SYSTEMS_RENDER_SYSTEM_H

#include "../engine/graphics/window.h"

/*
 * render_system_update
 *
 * Purpose: ECS-style render system entry point. In a full engine this
 * function would query the ECS world for entities with renderable
 * components (sprite, transform, etc.), compute world->screen transforms,
 * and issue draw calls through the engine's renderer API. In this minimal
 * example it simply demonstrates calling the engine drawing API.
 */
void render_system_update(Window *win);

#endif /* SYSTEMS_RENDER_SYSTEM_H */
