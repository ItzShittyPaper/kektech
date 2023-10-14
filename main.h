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
	
	snake_minigame = 8,

	loading_mode = 252,
	kkui_credit = 253,
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
int RNG_GenSeed(int rand_min, int rand_max);

#endif // MAIN_H_INCLUDED 
