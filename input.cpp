#include "libs.h"
#include "input.h"
#include "render.h"

/* 

KEYCODES:

Z = 0
X = 1
A = 2
S = 3

ARROWS:
	LEFT = 4
	RIGHT = 5
	UP = 6
	DOWN = 7

*/

SDL_Event e;

void I_ProcessKeys() {

	switch(e.key.keysym.sym) {

		case SDLK_z:
			I_ProcessInput(0);
			break;
		case SDLK_x:
			I_ProcessInput(1);
			break;
		case SDLK_a:
			I_ProcessInput(2);
			break;
		case SDLK_s:
			I_ProcessInput(3);
			break;
	
		case SDLK_LEFT:
			I_ProcessInput(4);
			break;
		case SDLK_RIGHT:
			I_ProcessInput(5);
			break;
		case SDLK_UP:
			I_ProcessInput(6);
			break;
		case SDLK_DOWN:
			I_ProcessInput(7);
			break;

		case SDLK_F11:
			ToggleFullscreen(window);
			break;

		default: return;

	}
}

bool I_ProcessInput(int key_code) {

	switch(key_code) {

		case 0:
			std::cout << "Z pressed" << std::endl;
			break;
		case 1:
			std::cout << "X pressed" << std::endl;
			break;
		case 2:
			std::cout << "A pressed" << std::endl;
			break;
		case 3:
			std::cout << "S pressed" << std::endl;
			break;

		case 4:
			std::cout << "LEFT pressed" << std::endl;
			break;
		case 5:
			std::cout << "RIGHT pressed" << std::endl;
			break;
		case 6:
			std::cout << "UP pressed" << std::endl;
			break;
		case 7:
			std::cout << "DOWN pressed" << std::endl;
			break;
	}
}
