bool init();
void kill();
bool loop();

/* THE MAIN SHARED VARIABLES */
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/*

GAME MODES / SCREENS
customizing those is advised

*/

enum modes {	
	main_mode = 0,
	dialog_mode = 1,

	kkui_crash = 254,
	kkui_dashboard = 255
} extern mode;

struct game_manager {

	char currentmap[128];
	int map_is_initialized;

} extern gamemgr;

// game-specific variables
extern const char *game_name;
extern const char *game_version;
extern const char *game_creator;
extern const char *game_info;
extern const char *game_url;

//Screen dimension constants
extern const int game_screen_width;
extern const int game_screen_height;

/*

DIALOG

*/

struct dialog_file {

	FILE* ptr;
	char ch[256];
	char* tag;

	char* file_buffer;

	char* current_dialog;

	bool is_triggered = false;
	int  is_menu      = 1;

	int target_num = 1;
	int line_num = 1;

} extern dialog;

struct dialog_menu {

	int option;
	int is_selected = 0;

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
/* npc interaction check code */
void NPC_HelperActivate(SDL_Rect player_collider, SDL_Rect tile, char* dialog_path);
void PLAYER_ResetVel();

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

/* 

AUDIO ARCHITECTURE

*/

struct audio_arch {

	/* a single music channel */
	Mix_Music *music = NULL;


} extern mixer;

/* 

COLOR DEFINITIONS

*/

/*
extern SDL_Color color0  = { 255, 255, 255 };
extern SDL_Color color1  = { 255, 255, 255 };
extern SDL_Color color2  = { 255, 255, 255 };
extern SDL_Color color3  = { 255, 255, 255 };
extern SDL_Color color4  = { 255, 255, 255 };
extern SDL_Color color5  = { 255, 255, 255 };
extern SDL_Color color6  = { 255, 255, 255 };
extern SDL_Color color7  = { 255, 255, 255 };
extern SDL_Color color8  = { 255, 255, 255 };
extern SDL_Color color9  = { 255, 255, 255 };
extern SDL_Color color10 = { 255, 255, 255 };
extern SDL_Color color11 = { 255, 255, 255 };
extern SDL_Color color12 = { 255, 255, 255 };
extern SDL_Color color13 = { 255, 255, 255 };
extern SDL_Color color14 = { 255, 255, 255 };
extern SDL_Color color15 = { 255, 255, 255 };
*/

/*

ANIMATION PLAYERS

*/

extern int animplayer0;
extern int animplayer1;
extern int animplayer2;
extern int animplayer3;
extern int animplayer4;
extern int animplayer5;
extern int animplayer6;
extern int animplayer7;

/* 

MISC

*/

extern SDL_Rect dest;

#endif // MAIN_H_INCLUDED 
