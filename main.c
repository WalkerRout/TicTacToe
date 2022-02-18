

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "lib/game.h"
#include "lib/rendering.h"
#include "lib/logic.h"

// Install GFX: https://github.com/RobLoach/sdl2_gfx
// Install SDL: https://www.youtube.com/watch?v=ybYMOKEW9IY

int main(int argc, char *argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr, "SDL could not iniatialize: SDL Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("TicTacToe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        fprintf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // use default graphics card to do rendering rather than CPU
    if(renderer == NULL){
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }



    game_t game = {
        .board = {EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY,
                  EMPTY, EMPTY, EMPTY},
        .player = PLAYER_X,
        .state = RUNNING_STATE
    };

    SDL_Event event;
    while(game.state != QUIT_STATE){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    game.state = QUIT_STATE;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    click_cell(&game,
                               event.button.y / CELL_HEIGHT,
                               event.button.x / CELL_WIDTH);

                default: {}
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer); // clear the renderer
        render_game(renderer, &game);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}