#include "libs.h"
#include "input.h"
#include "render.h"
#include "main.h"

/* 

== KEYCODES ==
action:
	Z = 0
	X = 1
	C = 2
	V = 3

movement:
	press:
		A / LEFT = 7
		D / RIGHT = 8
		W / UP = 9
		S / DOWN = 10
	release:
		A / LEFT = 11
		D / RIGHT = 12
		W / UP = 13
		S / DOWN = 14

*/

SDL_Event e;

void I_ProcessKeyDownEvent() {

	switch(e.key.keysym.sym) {

		/* action keys */
		case SDLK_z: I_ProcessInput(0); break;
		case SDLK_x: I_ProcessInput(1); break;
		case SDLK_c: I_ProcessInput(2); break;
		case SDLK_v: I_ProcessInput(3); break;

		/* movement keys, wasd and arrows, they basically do the same thing */
		case SDLK_LEFT: I_ProcessInput(7); break;
		case SDLK_RIGHT: I_ProcessInput(8); break;
		case SDLK_UP: I_ProcessInput(9); break;
		case SDLK_DOWN: I_ProcessInput(10); break;
		case SDLK_a: I_ProcessInput(7); break;
		case SDLK_d: I_ProcessInput(8); break;
		case SDLK_w: I_ProcessInput(9); break;
		case SDLK_s: I_ProcessInput(10); break;

		/* fullscreen toggle */
		case SDLK_F11: ToggleFullscreen(window); break;

		default: return;
	}
}

void I_ProcessKeyUpEvent() {

	switch(e.key.keysym.sym) {

		/* movement keys, wasd and arrows, they basically do the same thing */
		case SDLK_LEFT: I_ProcessInput(11); break;
		case SDLK_RIGHT: I_ProcessInput(12); break;
		case SDLK_UP: I_ProcessInput(13); break;
		case SDLK_DOWN: I_ProcessInput(14); break;
		case SDLK_a: I_ProcessInput(11); break;
		case SDLK_d: I_ProcessInput(12); break;
		case SDLK_w: I_ProcessInput(13); break;
		case SDLK_s: I_ProcessInput(14); break;

		default: return;
	}
}


bool I_ProcessInput(int key_code) {

	switch(key_code) {

		case 0:
			switch (mode) {
				case 1:
					dialog.target_num++;
					menu.is_selected = 1;
					break;
				default: break;
			}

			std::cout << "Z pressed" << std::endl; break;
		case 1:
			std::cout << "X pressed" << std::endl; break;
		case 2:
			std::cout << "C pressed" << std::endl; break;
		case 3:
			std::cout << "V pressed" << std::endl; break;
			
		case 7:
			switch (mode) {
				case 0:
            				player.vel_x -= 16 / player.speed; player.direction = 0; break;
				default: break;
			}

			std::cout << "LEFT / A pressed" << std::endl; break;
		case 8:
			switch (mode) {
				case 0:
            				player.vel_x += 16 / player.speed; player.direction = 1; break;
				default: break;
			}

			std::cout << "RIGHT / D pressed" << std::endl; break;
	        case 9:
			switch (mode) {
				case 0:
            				player.vel_y -= 16 / player.speed; player.direction = 2; break;
				case 1:
					menu.option--;
					break;
				default: break;
			}

			std::cout << "UP / W pressed" << std::endl; break;
	        case 10:
			switch (mode) {
				case 0:
					player.vel_y += 16 / player.speed; player.direction = 3; break;
				case 1:
					menu.option++;
					break;
				default: break;
			}

			std::cout << "DOWN / S pressed" << std::endl; break;

		/* 
		MOVEMENT KEY RELEASES
		*/

		case 11:
			switch (mode) {
				case 0:
            				player.vel_x += 16 / player.speed; break;
				default: break;
			}

			std::cout << "LEFT / A released" << std::endl; break;
		case 12:
			switch (mode) {
				case 0:
            				player.vel_x -= 16 / player.speed; break;
				default: break;
			}

			std::cout << "RIGHT / D released" << std::endl; break;
	        case 13:
			switch (mode) {
				case 0:
            				player.vel_y += 16 / player.speed; break;
				default: break;
			}

			std::cout << "UP / W released" << std::endl; break;
	        case 14:
			switch (mode) {
				case 0:
					player.vel_y -= 16 / player.speed; break;
				default: break;
			}

			std::cout << "DOWN / S released" << std::endl; break;
	}
}
