#ifndef CLIENT_DIALOG_H_INCLUDED
#define CLIENT_DIALOG_H_INCLUDED

#include <string>
#include <vector>

extern struct PotraitDefinition
{
	std::string charName;
	// path to the potrait sheet
	std::string pathName;
} potraitdefinition;

struct game_avatar {
	std::vector<PotraitDefinition*> cachedAvatars;
} extern* potraitmgr;

void UI_LoadAvatar(game_avatar* manager, char* path);
void UI_FreeAvatar(game_avatar* manager);
void UI_AddAvatar(game_avatar* manager, PotraitDefinition* definition);
void UI_ClearAvatar(game_avatar* manager);
void UI_RemoveAvatar(game_avatar* manager, PotraitDefinition* definition);
std::string UI_GetAvatar(game_avatar* manager, const char* avatar);
void UI_InitAvatars(game_avatar* manager);

char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2);
int UI_DialogBox(bool is_animated, const char* file);
void UI_Dialog(char* buffer);

#endif // CLIENT_DIALOG_H_INCLUDED 
