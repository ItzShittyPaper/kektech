#include "engine.h"
#include "dialog.h"

//game_avatar *portraitmanager;

void UI_FreeAvatar(game_avatar* manager)
{
	UI_ClearAvatar(manager);
	delete manager;
}

void UI_LoadAvatar(game_avatar* manager, const char* path) {

	FILE* file = fopen(path, "r");
	if (file == NULL) { snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING POTRAIT/AVATAR DEFINITIONS, FILE DOES NOT EXIST / PERMISSION DENIED\nAVATAR PATH: %s\n", path); mode = kkui_crash; return; }

	char avatarChunk[128];
	/* parse line by line */
	while (fgets(avatarChunk, sizeof(avatarChunk), file) != NULL) {

		PortraitDefinition* def = new PortraitDefinition();
		def->charName = std::string();
		def->pathName = std::string();
		
		// this should be the char name.
		char* tok = strtok(avatarChunk, ";");
		def->charName = tok;

		// this should be the char path
		tok = strtok(NULL, ";");
		def->pathName = tok;

		UI_AddAvatar(manager, def);
	}
}

void UI_AddAvatar(game_avatar* manager, PortraitDefinition* definition)
{
	printf(definition->charName.c_str());
	printf(definition->pathName.c_str());
	manager->cachedAvatars.push_back(definition);
}

void UI_ClearAvatar(game_avatar* manager)
{
	for (int i = 0; i < manager->cachedAvatars.size(); i++)
	{
		PortraitDefinition* def = manager->cachedAvatars[i];
	}

	manager->cachedAvatars.clear();
}

void UI_RemoveAvatar(game_avatar* manager, PortraitDefinition* definition)
{
	for (int i = 0; i < manager->cachedAvatars.size(); i++)
	{
		PortraitDefinition* def = manager->cachedAvatars[i];
		if (def == definition)
		{
			manager->cachedAvatars.erase(manager->cachedAvatars.begin() + i);
			return;
		}
	}
}

std::string UI_GetAvatar(game_avatar* manager, const char* avatar)
{
	for (int i = 0; i < manager->cachedAvatars.size(); i++)
	{

		PortraitDefinition* definition = manager->cachedAvatars[i];
		//printf("LOOK AT THIS SHIT: %s\n", definition->charName.c_str());
		if (strstr(avatar, definition->charName.c_str()) != 0)
		{
			definition->pathName.erase(std::remove(definition->pathName.begin(), definition->pathName.end(), '\n'), definition->pathName.cend());
			return definition->pathName;
		}
	}
	return std::string();
}

void UI_InitAvatars(game_avatar* manager) {
	UI_LoadAvatar(manager, "data/mat/avatars.avtr");
}

int UI_DialogBox(bool is_animated, const char* file) {

	if (mode == dialog_mode) {

		/* reset the players velocity */
		PLAYER_ResetVel();

		if (dialog.is_triggered == false) {
			dialog.target_num = 1;
			dialog.line_num = 1;
			dialog.ptr = fopen(file, "r");
			dialog.is_triggered = true;
		}

		if (dialog.line_num <= dialog.target_num) {
			read:
			fgets(dialog.ch, sizeof(dialog.ch), dialog.ptr);

			if (strstr(dialog.ch, "/===") != NULL) {

				strcpy(dialog.ch, strchr(dialog.ch, ' '));
				strcpy(dialog.ch, dialog.ch + 1);
				dialog.ch[strcspn(dialog.ch, "\n")] = 0;

				strncpy(gamemgr.currentmap, dialog.ch, 64); 

				UI_dashboard.animplayer = 255;
				animplayer6 = 0; animplayer7 = 0;
				dialog.character_count = 1;
				dialog.is_triggered = false;
				gamemgr.map_is_initialized = 0;
				mode = loading_mode;
				return 0;
			}

			else if (strstr(dialog.ch, "/0#") != NULL) {

				if (strcmp(dialog.character0, " ") == 0) { R_ResetPortraitAnim(); }

				char * pch;
				int i = 0;
				pch = strtok(dialog.ch, "; ");
				while (pch != NULL) {
					if (i == 1) {
						strncpy(dialog.character0, pch, 16);
					} else if (i == 2) {
						dialog.char0expr = atoi(pch);
					}
					pch = strtok (NULL, "; ");
					i++;
				}

				strncpy(dialog.current_character, dialog.character0, 16);
				dialog.character_count++;
				R_ResetPortraitAnim();
				goto read;
			}
			else if (strstr(dialog.ch, "/1#") != NULL) {
				if (strcmp(dialog.character1, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character1, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);

				dialog.character_count++;
				goto read;
			}
			else if (strstr(dialog.ch, "/2#") != NULL) {
				if (strcmp(dialog.character2, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character2, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);

				dialog.character_count++;
				goto read;
			}
			else if (strstr(dialog.ch, "/3#") != NULL) {
				if (strcmp(dialog.character3, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character3, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);

				dialog.character_count++;
				goto read;
			}

			else if (strstr(dialog.ch, "/0-") != NULL) { strncpy(dialog.character0, " ", 16); dialog.character_count--; R_ResetPortraitAnim(); goto read; }
			else if (strstr(dialog.ch, "/1-") != NULL) { strncpy(dialog.character1, " ", 16); dialog.character_count--; R_ResetPortraitAnim(); goto read; }
			else if (strstr(dialog.ch, "/2-") != NULL) { strncpy(dialog.character2, " ", 16); dialog.character_count--; R_ResetPortraitAnim(); goto read; }
			else if (strstr(dialog.ch, "/3-") != NULL) { strncpy(dialog.character3, " ", 16); dialog.character_count--; R_ResetPortraitAnim(); goto read; }

			else if (strstr(dialog.ch, "/=m=") != NULL) {

				char* head = strtok(dialog.ch, "; ");
				char* initbuf = (char*)malloc(sizeof(char) * 64);

				while (head != NULL) {

					if (strstr(head, "TEXT_1:") != NULL) { initbuf = strchr(head, ':'); initbuf[strcspn(initbuf, "\n")] = 0; menu.text1 = initbuf + 1; printf("TEXT_1: '%s'\n", menu.text1); }
					if (strstr(head, "TEXT_2:") != NULL) { initbuf = strchr(head, ':'); initbuf[strcspn(initbuf, "\n")] = 0; menu.text2 = initbuf + 1; printf("TEXT_2: '%s'\n", menu.text2); }
					if (strstr(head, "PATH_1:") != NULL) { initbuf = strchr(head, ':'); initbuf[strcspn(initbuf, "\n")] = 0; menu.path1 = initbuf + 1; printf("PATH_1: '%s'\n", menu.path1); }
					if (strstr(head, "PATH_2:") != NULL) { initbuf = strchr(head, ':'); initbuf[strcspn(initbuf, "\n")] = 0; menu.path2 = initbuf + 1; printf("PATH_2: '%s'\n", menu.path2); }

					//	printf("'%s'\n", head);
					head = strtok(NULL, ";");
				}

				dialog.is_menu = true;
				free(head);

			}

			dialog.line_num++;
		}

		if (animplayer6 > 223 && animplayer7 > 223 && dialog.render_characters == true) {

			std::string avatar = UI_GetAvatar(portraitmgr, dialog.character0);
			if (!avatar.empty())
			{
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, avatar.c_str()), dialog.char0expr);
			}

			avatar = UI_GetAvatar(portraitmgr, dialog.character1);
			if (!avatar.empty())
			{
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, avatar.c_str()), 0);
			}

			avatar = UI_GetAvatar(portraitmgr, dialog.character2);
			if (!avatar.empty())
			{
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, avatar.c_str()), 0);
			}

			avatar = UI_GetAvatar(portraitmgr, dialog.character3);
			if (!avatar.empty())
			{
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, avatar.c_str()), 0);
			}
		}

		/* the main dialog box */
		UI_FillRect(STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 72, GAME_VIEWPORT_WIDTH / UI_SCALE - 4, 72, true);
		UI_Rect(STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 72, GAME_VIEWPORT_WIDTH / UI_SCALE - 4, 72, true);

		/* the character name box */
		UI_FillRect(STANDARD_PADDING + 10, GAME_VIEWPORT_HEIGHT / UI_SCALE - 84, 72, 12, true);
		UI_Rect(STANDARD_PADDING + 10, GAME_VIEWPORT_HEIGHT / UI_SCALE - 84, 72, 12, true);

		/* the label */
		if (animplayer6 > 223 && animplayer7 > 223) {
			//UI_TextLabelEx(2 + STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 72, 255, 255, 255, dialog.ch, GAME_VIEWPORT_WIDTH / UI_SCALE - STANDARD_PADDING, true);
			R_RenderText(fontshader, dialog.ch, (2 + STANDARD_PADDING) * UI_SCALE, (GAME_VIEWPORT_HEIGHT / UI_SCALE - 72) * UI_SCALE, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
			//UI_TextLabelEx(10 + STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 84, 255, 255, 255, dialog.current_character, GAME_VIEWPORT_WIDTH / UI_SCALE - STANDARD_PADDING, true);
			R_RenderText(fontshader, dialog.current_character, (10 + STANDARD_PADDING) * UI_SCALE, (GAME_VIEWPORT_HEIGHT / UI_SCALE - 84) * UI_SCALE, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
		}
	}
	return 0;
}

char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2) {

	if (mode == dialog_mode) {

		UI_dashboard.animplayer = 255;
		animplayer6 = 0; animplayer7 = 0;
		dialog.character_count = 1;
		dialog.is_triggered = false;

		PLAYER_ResetVel();
		/* animated rectangle code */

		if (menu.option > 1)
			menu.option = 0;
		else if (menu.option < 0)
			menu.option = 0;
		
		/* check for selection */
		if (menu.is_selected == 1) {
			menu.is_selected = 0;
			dialog.is_menu = false;
			mode = loading_mode;

			switch (menu.option) {

				case 0:
					printf("%s\n", path_1);
					return (char*)path_1;
					break;
				case 1:
					printf("%s\n", path_2);
					return (char*)path_2;
					break;
				default:
					printf("uhmmm wtf\n");
					exit(1);
			}
		}

		for (int i = 0; i < 2; i++) {
			UI_FillRect(6, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), 308, 33, false);

			if (i == menu.option) { UI_SelectRect(6, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), 308, 33, false); }
			else { UI_Rect(6, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), 308, 33, false); }
				
			if (i == 0) {
				//UI_TextLabel(8, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), label_1, 244);
				R_RenderText(fontshader, label_1, 8 * UI_SCALE, ((GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35)) * UI_SCALE, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			} else {
				//UI_TextLabel(8, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), label_2, 244);
				R_RenderText(fontshader, label_2, 8 * UI_SCALE, ((GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35)) * UI_SCALE, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			}
		}
	}

	return NULL;

}

void UI_Dialog(char* buffer) {

	PLAYER_ResetVel();

	if (dialog.is_menu != false) {
		dialog.current_dialog = UI_Menu(true, menu.text1, menu.text2, menu.path1, menu.path2);
	}
	else {
		UI_DialogBox(true, dialog.current_dialog);
	}
}
