

#include "logic.h"



void switch_player(game_t *game){

	if(game->player == PLAYER_X){
		game->player = PLAYER_O;
	} else {
		game->player = PLAYER_X;
	}
}




uint8_t check_player_won(game_t *game, 
					  	 uint8_t player){

	uint8_t row_count = 0;
	uint8_t column_count = 0;
	uint8_t r_diag_count = 0;
	uint8_t l_diag_count = 0;


	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(game->board[i * N + j] == player){
				row_count++;
			}

			if(game->board[j * N + i] == player){
				column_count++;
			}
		}

		if(row_count >= N || column_count >= N){
			return 1;
		}

		row_count = 0;
		column_count = 0;

		if(game->board[i * N + i] == player){
			r_diag_count++;
		}

		if(game->board[i * N + N - i - 1] == player){
			l_diag_count++;
		}
	}

	return (l_diag_count >= N || r_diag_count >= N);
}



uint8_t count_cells(const int* board, 
				 	uint8_t cell){

	uint8_t count = 0;
	for(int i = 0; i < N * N; ++i){
		if(board[i] == cell){
			count++;
		}
	}

	return count;
}



void game_over_condition(game_t *game){

	if(check_player_won(game, PLAYER_X)){
		game->state = PLAYER_X_WON_STATE;
	} else if (check_player_won(game, PLAYER_O)){
		game->state = PLAYER_O_WON_STATE;
	} else if (count_cells(game->board, EMPTY) == 0){
		game->state = TIE_STATE;
	}
}



void player_turn(game_t *game, 
				 int row, int column){

	if(game->board[row * N + column] == EMPTY){
		game->board[row * N + column] = game->player;
		switch_player(game);
		game_over_condition(game);
	}
}



void reset_game(game_t *game){

	game->player = PLAYER_X;
	game->state = RUNNING_STATE;

	for(int i = 0; i < N * N; ++i){
		game->board[i] = EMPTY;
	}
}



void click_cell(game_t *game, 
				int row, int column){

	if(game->state == RUNNING_STATE){
		player_turn(game, row, column);
	} else {
		reset_game(game);
	}
}