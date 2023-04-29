/* THE UI CODE FOR THE ENGINE */

#include "libs.h"

#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

struct game_ui {

	SDL_Texture *text;

} extern UI;

void UI_TextBox();
void UI_TextLabel(int pos_x, int pos_y, const char *label, int wrap_length);
void UI_Rect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_SelectRect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_FillRect(int pos_x, int pos_y, int width, int height, bool is_animated);
void UI_DialogBox(bool is_animated, const char* file, const char* text_id);
char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2);
void UI_Dialog(char* buffer);

#endif // UI_H_INCLUDED 

extern std::string textbox_input;
