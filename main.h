bool init();
void kill();
bool loop();

/* THE MAIN SHARED VARIABLES */
#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

/*

GAME MODES / SCREENS

*/

enum modes {
	main_mode = 0,
	dialog_mode = 1
} extern mode;

/*

DIALOG

*/

struct dialog_file {

	FILE* ptr;
	char ch[256];
	char* tag;

	char* file_buffer;

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
