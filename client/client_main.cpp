#include "engine.h"
#include "client_render.h"
#include "client_main.h"
#include "dialog.h"
#include "snake.h"

void PLAYER_Init() {

	player.collider.x = 0;
	player.collider.y = 0;
	player.collider.w = 16;
	player.collider.h = 16;

}

void PLAYER_Move() {

	//Move the dot left or right
	player.pos_x += player.vel_x;
	player.collider.x = player.pos_x;
    
 	//Move the dot up or down
	player.pos_y += player.vel_y;
	player.collider.y = player.pos_y;

	/* stop and start the animation depending on the player movement */
	/* i know that i should use the || (OR) operator here, but it doesnt fucking work */
	if (player.vel_y != 0) { player.is_moving = 1; }
	else if (player.vel_x != 0) { player.is_moving = 1; }
	else { player.is_moving = 0; animplayer5 = 0; }
}

void PLAYER_ResetVel() {

	player.is_moving = 0;
	player.vel_y = 0;
	player.vel_x = 0;

}

void NPC_HelperActivate(SDL_Rect player_collider, SDL_Rect tile, char* dialog_path) {

	if (M_CheckCollision(player_collider, tile) && is_interacting == 1) {
		dialog.current_dialog = dialog_path;
		mode = dialog_mode;
	}

}

/* ============================= */

bool ClientInput(int key_code) {

	switch(key_code) {

		case 0:
			switch (mode) {
				case 0:
					is_interacting = 1;
					break;
				case 1:
					dialog.target_num++;
					if(dialog.is_menu == true)
						menu.is_selected = 1;
					break;
				/* main menu */

				case 253:
					mode = kkui_dashboard;
					gamemgr.map_is_initialized = 0;
					UI_SendLog("thank you for playing the game");
					UI_SendLog("hope you enjoyed it!");
					break;

				case 255:
					mode = loading_mode;
					gamemgr.map_is_initialized = 0;
					//SDL_DestroyTexture(UI_dashboard.menu_background);
					break;

				default: break;
			}

			A_PlaySFX("data/mus/select.wav");
//			Mix_PlayChannel( -1, A_GetSoundEffect(sfxmgr, "select"), 0);
			std::cout << "Z pressed" << std::endl; break;
		case 1:

			switch (mode) {

				/* main menu */
				case 255:
					UI_dashboard.menu_background = IMG_LoadTexture(renderer, "leo/bmp/about.png");
					//SDL_DestroyTexture(UI_dashboard.menu_background);
					break;

				default: break;
			}



			std::cout << "X pressed" << std::endl; break;
		case 2:
			std::cout << "C pressed" << std::endl; break;
		case 3:
			switch(mode) {
				case 1:
					mode = snake_minigame; break;

				case 8:
					mode = main_mode; break;

			}

			std::cout << "V pressed" << std::endl; break;
			
		case 7:
			switch (mode) {
				case 0:
            				player.vel_x -= 16 / player.speed; player.direction = 0; break;
				case 8:
					snake.direction = 1; break;
				default: break;
			}

			std::cout << "LEFT / A pressed" << std::endl; break;
		case 8:
			switch (mode) {
				case 0:
            				player.vel_x += 16 / player.speed; player.direction = 1; break;
				case 8:
					snake.direction = 0; break;
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
				case 8:
					snake.direction = 2; break;
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
				case 8:
					snake.direction = 3; break;
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
	return true;

}

bool ProcessInput() {

	if (player.is_alive == true)
		PLAYER_Move();

	return true;

}

bool ClientInit() {

	strncpy(dialog.character0, " ", 1); strncpy(dialog.character1, " ", 1); strncpy(dialog.character2, " ", 1); strncpy(dialog.character3, " ", 1);
	SNAKE_InitGame();
	return true;

}

void ClientGameLoop() {

	if (mode == main_mode || mode == dialog_mode) {

		/*
			GAME LOGIC
		*/

		if (gamemgr.is_paused == false)
			ProcessInput();
		//A_MusicUpdateEvent();

		/* ------------------------- */

		/*
			DRAWING
		*/

		M_ReadMapFile(gamemgr.currentmap, texturemgr);

		if (player.is_alive == true)
			R_DrawPlayer(R_GetMaterial(texturemgr, "leo_sheet"), player.direction);

		/* ------------------------- */

		/*
			UI
		*/

		/* show the game log on the top-left */
		UI_ShowLog(UI_log.logbuffer);

		/* mode checks i guess */
		UI_Dialog(dialog.current_dialog);

		/* ------------------------ */

	}
	else if (mode == snake_minigame) {

		SNAKE_RenderGame();
		SNAKE_GameStep();

	}

}

void ClientLoadingAnim() {

	if (UI_dashboard.animplayer > 0) {
		/* render the map background */
		SDL_SetTextureAlphaMod(UI_dashboard.menu_background, UI_dashboard.animplayer);
		UI_dashboard.animplayer -= 16;
	}
	if (UI_dashboard.animplayer <= 0 ) {
		mode = main_mode;
	}

	UI_ShowLog(UI_log.logbuffer);	

}
