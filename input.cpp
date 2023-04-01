#include "libs.h"
#include "input.h"
#include "render.h"

/* 

== KEYCODES ==
action:
	Z = 0
	X = 1
	C = 2
	V = 3

movement:
	A / LEFT = 7
	D / RIGHT = 8
	W / UP = 9
	S / DOWN = 10

*/

SDL_Event e;

void I_ProcessKeys() {

	switch(e.key.keysym.sym) {

		/* action keys */
		case SDLK_z:
			I_ProcessInput(0);
			break;
		case SDLK_x:
			I_ProcessInput(1);
			break;
		case SDLK_c:
			I_ProcessInput(2);
			break;
		case SDLK_v:
			I_ProcessInput(3);
			break;

		/* movement keys, wasd and arrows, they basically do the same thing */
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
		case SDLK_w:
			I_ProcessInput(7);
			break;
		case SDLK_a:
			I_ProcessInput(8);
			break;
		case SDLK_s:
			I_ProcessInput(9);
			break;
		case SDLK_d:
			I_ProcessInput(10);
			break;

		/* fullscreen toggle */
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
			std::cout << "C pressed" << std::endl;
			break;
		case 3:
			std::cout << "V pressed" << std::endl;
			break;

			
		case 7:
			std::cout << "LEFT / A pressed" << std::endl;
			break;
		case 8:
			std::cout << "RIGHT / D pressed" << std::endl;
			break;
	        case 9:
			std::cout << "UP / W pressed" << std::endl;
			break;
	        case 10:
			std::cout << "DOWN / S pressed" << std::endl;
			break;
	}
	}
}
