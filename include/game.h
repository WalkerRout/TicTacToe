
#ifndef GAME_H
#define GAME_H

#define N 3
#define WIDTH 640
#define HEIGHT 480
#define CELL_WIDTH (WIDTH / N)
#define CELL_HEIGHT (HEIGHT / N)

#define EMPTY 0
#define PLAYER_X 1
#define PLAYER_O 2

#define RUNNING_STATE 0
#define PLAYER_X_WON_STATE 1
#define PLAYER_O_WON_STATE 2
#define TIE_STATE 3
#define QUIT_STATE 4


typedef struct {
	int board[N * N];
	int player; // X or O
	int state; // Running or over (3 states)
} game_t;

#endif