#include "engine.h"
#include "snake.h"

/* init the snake struct */
struct snake_minigame snake;

bool SNAKE_InitGame() {

	snake.framecount = 0;

	snake.length = 1;
	snake.direction = 0; /* right */
	snake.speed = SNAKE_SPEED; /* higher is SLOWER */
	snake.score = 0; /* higher is SLOWER */

	snake.pos_x = 2;
	snake.pos_y = 2;

	snake.apple_x = 6;
	snake.apple_y = 3;

	snake.is_alive = true;

	//mode = snake_minigame;

	return true;

}

void SNAKE_NewApplePos() {

	snake.apple_x = RNG_GenSeed(1, BOARD_SIZE_X);
	snake.apple_y = RNG_GenSeed(1, BOARD_SIZE_Y);

}

int SNAKE_RenderGameASCII() {

	int row = 0;
	int column = 0;

	if (snake.is_alive == true) {

		while (row <= BOARD_SIZE_Y) {

			while (column <= BOARD_SIZE_X) {

				if (row == snake.pos_y && column == snake.pos_x)
					printf("%s", "S");
				else if (row == snake.apple_y && column == snake.apple_x)
					printf("%s", "A");
				else	
					printf("%s", " ");

				column++;

			}
			column = 0;
			printf("\n");
			row++;

		}

		while (column <= BOARD_SIZE_X) { printf("-"); column++; }
		printf(" score: %d alive: %b", snake.score, snake.is_alive);
		printf("\n");

		/* scoring */
		if (snake.pos_y == snake.apple_y && snake.pos_x == snake.apple_x) {
			SNAKE_NewApplePos();
			snake.score++;
		}

	}

	return 0;

}

int SNAKE_RenderGame() {

	int row = 0;
	int column = 0;

	if (snake.is_alive == true) {

		while (row <= BOARD_SIZE_Y) {

			while (column <= BOARD_SIZE_X) {

				if (row == snake.pos_y && column == snake.pos_x) {
					UI_TextLabelEx((column + SNAKE_UI_OFFSET_X) * CELL_WIDTH, (row + SNAKE_UI_OFFSET_Y) * CELL_HEIGHT, 255, 255, 255, "S", 9999, true); printf("%s", "S");
				}
				else if (row == snake.apple_y && column == snake.apple_x) {
					UI_TextLabelEx((column + SNAKE_UI_OFFSET_X) * CELL_WIDTH, (row + SNAKE_UI_OFFSET_Y) * CELL_HEIGHT, 255, 255, 255, "A", 9999, true); printf("%s", "A");
				}
				else {
					printf("%s", " ");
				}
				column++;

			}
			column = 0;
			printf("\n");
			row++;

		}

		while (column <= BOARD_SIZE_X) { printf("-"); column++; }

		/* scoring */
		if (snake.pos_y == snake.apple_y && snake.pos_x == snake.apple_x) {
			SNAKE_NewApplePos();
			snake.score++;
		}

	}
	sprintf(snake.status, "score: %d alive: %b", snake.score, snake.is_alive);
	UI_TextLabelEx(0 + SNAKE_UI_OFFSET_X * CELL_WIDTH, (SNAKE_UI_OFFSET_Y - 1) * CELL_HEIGHT, 255, 255, 255, "SNAKE EATER MINIGAME | LICENSED TO: DONIX", 9999, true);
	UI_TextLabelEx(0 + SNAKE_UI_OFFSET_X * CELL_WIDTH, (BOARD_SIZE_Y + SNAKE_UI_OFFSET_Y + 1) * CELL_HEIGHT, 255, 255, 255, "----------------------------------------------", 9999, true);
	UI_TextLabelEx((BOARD_SIZE_X + SNAKE_UI_OFFSET_X + 1) * CELL_WIDTH, (0 + SNAKE_UI_OFFSET_Y) * CELL_HEIGHT, 255, 255, 255, " |||||||| ", 2, true);
	UI_TextLabelEx(0 + SNAKE_UI_OFFSET_X * CELL_WIDTH, (BOARD_SIZE_Y + SNAKE_UI_OFFSET_Y + 2) * CELL_HEIGHT, 255, 255, 255, snake.status, 9999, true);

	return 0;

}

//int SNAKE_
//int RNG_GenSeed(int rand_min, int rand_max) {

int SNAKE_GameStep() {

	if (snake.framecount % snake.speed == 0) {

		switch(snake.direction) {

			/* right */
			case 0:
				snake.pos_x += 1;
				break;
			/* left  */
			case 1:
				snake.pos_x -= 1;
				break;
			/* up    */
			case 2:
				snake.pos_y -= 1;
				break;
			/* down  */	
			case 3:
				snake.pos_y += 1;
				break;

		}
		snake.framecount = 0;
	}

	if (snake.pos_x > BOARD_SIZE_X || snake.pos_y > BOARD_SIZE_Y || snake.pos_x < 1 || snake.pos_y < 1) {
		snake.is_alive = false;
	}

	snake.framecount++;
	return true;

}
