

#include "rendering.h"


const SDL_Color PLAYER_X_COLOUR = {.r = 255, .g = 25, .b = 50};
const SDL_Color PLAYER_O_COLOUR = {.r = 50, .g = 10, .b = 255};
const SDL_Color TIE_COLOUR = {.r = 100, .g = 100, .b = 100};
const SDL_Color GRID_COLOUR = {.r = 255, .g = 255, .b = 255};



void render_grid(SDL_Renderer *renderer, 
				 const SDL_Color *colour){

	SDL_SetRenderDrawColor(renderer, colour->r, colour->g, colour->b, 255);
	for(int i = 1; i < N; ++i){
		SDL_RenderDrawLine(renderer,
						   i * CELL_WIDTH, 0,
					   	   i * CELL_WIDTH, HEIGHT);
		SDL_RenderDrawLine(renderer,
						   0, i * CELL_HEIGHT,
					   	   WIDTH, i * CELL_HEIGHT);
	}
}



void render_x(SDL_Renderer *renderer,
			  int row, int column,
			  const SDL_Color *colour){

	const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
	const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;


	// First half of X
	thickLineRGBA(renderer,
				  center_x - half_box_side,
				  center_y - half_box_side,
				  center_x + half_box_side,
				  center_y + half_box_side,
				  10,
				  colour->r,
				  colour->g,
				  colour->b,
				  255);

	// Second half of X
	thickLineRGBA(renderer,
				  center_x + half_box_side,
				  center_y - half_box_side,
				  center_x - half_box_side,
				  center_y + half_box_side,
				  10,
				  colour->r,
				  colour->g,
				  colour->b,
				  255);
}



void render_o(SDL_Renderer *renderer,
			  int row, int column,
			  const SDL_Color *colour){

	const float half_box_side = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
	const float center_x = CELL_WIDTH * 0.5 + column * CELL_WIDTH;
	const float center_y = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

	filledCircleRGBA(renderer,
					 center_x,
				 	 center_y,
				  	 half_box_side + 5,
				  	 colour->r,
				  	 colour->g,
				  	 colour->b,
				  	 255);

	filledCircleRGBA(renderer,
					 center_x,
				 	 center_y,
				  	 half_box_side - 5,
				  	 0,
				  	 0,
				  	 0,
				  	 255);
}



void render_board(SDL_Renderer *renderer, 
				  const int *board, 
				  const SDL_Color *player_x_colour, const SDL_Color *player_o_colour){
	
	/*
	 * i = 0
	 * j = 0
	 * N = 3

	 * board[i * N + j] 0 * 3 + 0 = 0
	 * board[i * N + j] 0 * 3 + 1 = 1
	 * board[i * N + j] 0 * 3 + 2 = 2
	 * board[i * N + j] 1 * 3 + 0 = 3
	 * board[i * N + j] 1 * 3 + 1 = 4
	 * etc
	 *
	 */

	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){

			switch(board[i * N + j]){
				case PLAYER_X:
					render_x(renderer, i, j, player_x_colour);
					break;

				case PLAYER_O:
					render_o(renderer, i, j, player_o_colour);
					break;

				default: {}
			}
		}
	}

}



void render_running_state(SDL_Renderer *renderer, 
						  const game_t *game){

	render_grid(renderer, &GRID_COLOUR);
	render_board(renderer,
				 game->board,
				 &PLAYER_X_COLOUR,
				 &PLAYER_O_COLOUR);
}



void render_game_over_state(SDL_Renderer *renderer, 
							const game_t *game, 
							const SDL_Color *colour){

	render_grid(renderer, colour);
	render_board(renderer,
				 game->board,
				 colour,
				 colour);
}



void render_game(SDL_Renderer *renderer,
				 const game_t *game){

    switch(game->state){
    	case RUNNING_STATE:
    		render_running_state(renderer, game);
    		break;

    	case PLAYER_X_WON_STATE:
    		render_game_over_state(renderer, game, &PLAYER_X_COLOUR);
    		break;

    	case PLAYER_O_WON_STATE:
    		render_game_over_state(renderer, game, &PLAYER_O_COLOUR);
    		break;

    	case TIE_STATE:
    		render_game_over_state(renderer, game, &TIE_COLOUR);
    		break;
    }
}
