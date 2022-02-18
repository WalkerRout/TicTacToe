
#ifndef RENDERING_H
#define RENDERING_H

#include <SDL2/SDL.h>
#include "SDLExtensions/SDL2_gfxPrimitives.h"
#include "game.h"

void render_game(SDL_Renderer *renderer, const game_t *game);

#endif