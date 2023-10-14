#ifndef CLIENT_DIALOG_H_INCLUDED
#define CLIENT_DIALOG_H_INCLUDED

char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2);
int UI_DialogBox(bool is_animated, const char* file);
void UI_Dialog(char* buffer);

#endif // CLIENT_DIALOG_H_INCLUDED 
