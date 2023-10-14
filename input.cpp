#include "libs.h"
#include "input.h"
#include "render.h"
#include "audio.h"
#include "ui.h"
#include "main.h"

//#include "client_main.h"

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
//		case SDLK_a: I_ProcessInput(7); break;
//		case SDLK_d: I_ProcessInput(8); break;
//		case SDLK_w: I_ProcessInput(9); break;
//		case SDLK_s: I_ProcessInput(10); break;

		/* fullscreen toggle */
		case SDLK_F11: ToggleFullscreen(window); break;

		default: return;
	}
}

void I_ProcessPauseEvent() {

	if (e.key.keysym.sym == SDLK_F10) {
		/* pause */
		if (gamemgr.is_paused == false) { PLAYER_ResetVel(); gamemgr.is_paused = true; PLAYER_ResetVel(); } else { gamemgr.is_paused = false; PLAYER_ResetVel(); }
	}

}

void I_ProcessKeyUpEvent() {

	switch(e.key.keysym.sym) {

		/* movement keys, wasd and arrows, they basically do the same thing */
		case SDLK_LEFT: I_ProcessInput(11); break;
		case SDLK_RIGHT: I_ProcessInput(12); break;
		case SDLK_UP: I_ProcessInput(13); break;
		case SDLK_DOWN: I_ProcessInput(14); break;
//		case SDLK_a: I_ProcessInput(11); break;
//		case SDLK_d: I_ProcessInput(12); break;
//		case SDLK_w: I_ProcessInput(13); break;
//		case SDLK_s: I_ProcessInput(14); break;

		default: return;
	}
}


bool I_ProcessInput(int key_code) {

	if (gamemgr.is_paused == true) { goto skip; }

	ClientInput(key_code);

	skip:
	return true;
}
