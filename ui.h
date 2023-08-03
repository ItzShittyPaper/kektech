/* THE UI CODE FOR THE ENGINE */


#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "libs.h"

struct game_ui {

	SDL_Texture *text;

} extern UI;

struct ui_log {

	std::vector<std::string> log_vector;
	std::vector<int>::iterator it;
	int ioffset;
	char* logbuffer;

	// this is now using a deprecated animation method, but idc tbh
	int logtextanimation;

} extern UI_log;

struct ui_nsod {

	char* crash_logbuffer;

} extern UI_nsod;

struct ui_dashboard {
	SDL_Texture* menu_background;
} extern UI_dashboard;

void UI_SendLog(const char* text);
void UI_InitLog();
void UI_ShowLog(const char* text);
void UI_TextBox();
void UI_TextLabel(int pos_x, int pos_y, const char *label, int wrap_length);
void UI_Rect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_SelectRect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_FillRect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_DialogBox(bool is_animated, const char* file);
char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2);
void UI_Dialog(char* buffer);

void UI_CrashScreen(const char *label);

#endif // UI_H_INCLUDED 

extern std::string textbox_input;
