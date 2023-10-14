/* THE CLIENT_MAIN SHARED VARIABLES */
/* HERE YOU SHOULD START CODING YOUR GAME */
#ifndef CLIENT_MAIN_H_INCLUDED
#define CLIENT_MAIN_H_INCLUDED

#include "engine.h"

/*

DIALOG

*/

struct dialog_file {

	bool render_characters = false;
	bool is_triggered = false;
	bool is_menu;

	int character_count = 1;
	int target_num = 1;
	int line_num = 1;

	FILE* ptr;
	char* tag;
	char* file_buffer;
	char* current_dialog = (char*)malloc(sizeof(char) * 16);
	
	char ch[512];
	char current_character[16];
	char character0[16];
	char character1[16];
	char character2[16];
	char character3[16];

} extern dialog;

struct dialog_menu {

	int option;
	int is_selected = 0;

	char* text1 = (char*)malloc(sizeof(char) * 32);
	char* text2 = (char*)malloc(sizeof(char) * 32);
	char* path1 = (char*)malloc(sizeof(char) * 16);
	char* path2 = (char*)malloc(sizeof(char) * 16);


} extern menu;

/*

PLAYER

*/

struct player_ent {

	bool is_alive = false;

	/* higher is slower */
	int speed = 16;

	int pos_x = 0;
	int pos_y = 0;
	int vel_x = 0;
	int vel_y = 0;

	/* PLAYERS FACING DIRECTION
		0 = LEFT
		1 = RIGHT
		2 = UP
		3 = DOWN
	*/
	int direction = 0;
	int is_moving = 0;

	SDL_Rect collider;

} extern player;

/*

NPC

*/

/* global variable checking if the player is interacting with an NPC */
extern int is_interacting;

struct helper_ent {

	/* the direction and position the npc is looking at */
	int direction;
	int pos_x;
	int pos_y;

	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Rect intrect;

	/* dialog file to refer to */
	char* dialog;


};

/* GAME-CRITICAL FUNCTIONS */
void PLAYER_Init();
void PLAYER_Move();
void PLAYER_ResetVel();
void NPC_HelperActivate(SDL_Rect player_collider, SDL_Rect tile, char* dialog_path);
void ClientGameLoop();
void ClientLoadingAnim();

bool ClientInit();
bool ProcessInput();
bool ClientInput(int key_code);

#endif // CLIENT_MAIN_H_INCLUDED 
