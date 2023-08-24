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
	loading_mode = 2,

	kkui_crash = 254,
	kkui_dashboard = 255
} extern mode;

struct game_manager {

	char currentmap[128];
	int map_is_initialized;

	bool is_paused = false;

	uint64_t frame_starttime;
	uint64_t frame_endtime;
	uint64_t frame_deltatime;

} extern gamemgr;

// game-specific variables
extern const char *game_name;
extern const char *game_version;
extern const char *game_creator;
extern const char *game_info;
extern const char *game_url;

extern const int game_viewport_width;
extern const int game_viewport_height;

//Screen dimension constants
extern const int game_screen_width;
extern const int game_screen_height;

/*

DIALOG

*/

struct dialog_file {

	FILE* ptr;
	char ch[512];
	char *tag;

	char* file_buffer;

	char* current_dialog = (char*)malloc(sizeof(char) * 16);
	char current_character[64];
	char character0[64];
	char character1[64];
	char character2[64];
	char character3[64];
	int character_count = 1;
	bool render_characters = false;

	bool is_triggered = false;
	bool is_menu = false;

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

COLOR DEFINITIONS

*/

/*

ANIMATION PLAYERS

*/

extern int animplayer5;
extern int animplayer6;
extern int animplayer7;

/* 

MISC

*/

extern SDL_Rect dest;

#endif // MAIN_H_INCLUDED 
