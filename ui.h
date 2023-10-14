/* THE UI CODE FOR THE ENGINE */


#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include "libs.h"

#define UI_SCALE 2
#define STANDARD_PADDING 2

#define LOG_SHOW_LENGTH 320

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
	int animplayer;
} extern UI_dashboard;

struct ui_rgbcolor {

	int r;
	int g;
	int b;

};

void UI_SendLog(const char* text);
void UI_InitLog();
void UI_ShowLog(const char* text);
void UI_TextBox();
ui_rgbcolor UI_RGBColorReturn(char* chunk);
void UI_TextLabel(int pos_x, int pos_y, const char *label, int wrap_length);
void UI_TextLabelEx(int pos_x, int pos_y, uint8_t r, uint8_t g, uint8_t b,  const char *label, int wrap_length, bool is_scaled);
void UI_Rect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_SelectRect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_SelectRectEx(int pos_x, int pos_y, int width, int height, uint8_t r, uint8_t g, uint8_t b, bool is_animated);
void UI_FillRect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_FillRectEx(int pos_x, int pos_y, int width, int height, uint8_t r, uint8_t g, uint8_t b, bool is_animated);
void UI_WindowFrameEx(int pos_x, int pos_y, int width, int height, uint8_t r_bg, uint8_t g_bg, uint8_t b_bg, uint8_t r_text, uint8_t g_text, uint8_t b_text, const char* title);
void UI_CrashScreen(const char *label);

#endif // UI_H_INCLUDED 

extern std::string textbox_input;
