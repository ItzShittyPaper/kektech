#include "libs.h"
#include "input.h"
#include "render.h"

/* 

KEYCODES:
W = 0
A = 1
S = 2
D = 3
Z = 4
X = 5
S = 6

ARROWS:
	LEFT = 7
	RIGHT = 8
	UP = 9
	DOWN = 10

*/

SDL_Event e;

void I_ProcessKeys() {

	switch(e.key.keysym.sym) {
                case SDLK_w:
			I_ProcessInput(0);
			break;
		case SDLK_a:
			I_ProcessInput(1);
			break;
		case SDLK_s:
			I_ProcessInput(2);
			break;
		case SDLK_d:
			I_ProcessInput(3);
			break;
		case SDLK_z:
			I_ProcessInput(4);
			break;
		case SDLK_x:
			I_ProcessInput(5);
			break;
		case SDLK_s:
			I_ProcessInput(6);
			break;
	
		case SDLK_LEFT:
			I_ProcessInput(7);
			break;
		case SDLK_RIGHT:
			I_ProcessInput(8);
			break;
		case SDLK_UP:
			I_ProcessInput(9);
			break;
		case SDLK_DOWN:
			I_ProcessInput(10);
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
			std::cout << "W pressed" << std::endl;
			break;
		case 1:
			std::cout << "A pressed" << std::endl;
			break;
		case 2:
			std::cout << "S pressed" << std::endl;
			break;
		case 3:
			std::cout << "D pressed" << std::endl;
			break;
		case 4:
			std::cout << "Z pressed" << std::endl;
			break;
		case 5:
			std::cout << "X pressed" << std::endl;
			break;
		case 6:
			std::cout << "S pressed" << std::endl;
			break;
		case 7:
			std::cout << "LEFT_ARROW pressed" << std::endl;
			break;
		case 8:
			std::cout << "RIGHT_ARROW pressed" << std::endl;
			break;
	        case 9:
			std::cout << "UP_ARROW pressed" << std::endl;
			break;
	        case 10:
			std::cout << "DOWN_ARROW pressed" << std::endl;
			break;
	}
	}
}
