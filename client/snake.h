#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "engine.h"

#define SNAKE_UI_OFFSET_X 1
#define SNAKE_UI_OFFSET_Y 3

#define BOARD_SIZE_X 16
#define BOARD_SIZE_Y 12
#define CELL_WIDTH 5
#define CELL_HEIGHT 6
/* the lower it is, the faster the snake gets */
#define SNAKE_SPEED 10
#define SNAKE_MAX_LENGTH 32

/* minigame data uwu */
struct snake_minigame {

	int framecount;

	int length;
	int direction;
	int speed;
	int score;

	int pos_x;
	int pos_y;

	int apple_x;
	int apple_y;

	char status[24];

	bool is_alive;

} extern snake;

void SNAKE_NewApplePos();
bool SNAKE_InitGame();
int SNAKE_RenderGame();
int SNAKE_GameStep();

#endif // SNAKE_H_INCLUDED 
