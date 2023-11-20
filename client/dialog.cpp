#include "engine.h"

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

			//	char *head = strtok(dialog.ch, "; ");
			//	char *initbuf = (char*)malloc(sizeof(char) * 64);

			//	while (head != NULL) {

			//		if(strstr(head, "CHARNAME:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; strncpy(dialog.character0, initbuf + 1, 16); printf("%s\n", initbuf + 1); }
		
			//		printf("'%s'\n", head);
			//		head = strtok(NULL, ";");
			//	}	

			//	free(head);

				if (strcmp(dialog.character0, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character0, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);
				R_ResetPortraitAnim();
				goto read;
			} 
			else if (strstr(dialog.ch, "/1#") != NULL) {
				if (strcmp(dialog.character1, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character1, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);
				goto read;
			}
			else if (strstr(dialog.ch, "/2#") != NULL) {
				if (strcmp(dialog.character2, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character2, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);
				goto read;
			} 
			else if (strstr(dialog.ch, "/3#") != NULL) {
				if (strcmp(dialog.character3, " ") == 0) { R_ResetPortraitAnim(); }
				strncpy(dialog.character3, dialog.ch, 16);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 16);
				goto read;
			} 

			else if (strstr(dialog.ch, "/0-") != NULL) { strncpy(dialog.character0, " ", 16); R_ResetPortraitAnim(); goto read; }
			else if (strstr(dialog.ch, "/1-") != NULL) { strncpy(dialog.character1, " ", 16); R_ResetPortraitAnim(); goto read; }
			else if (strstr(dialog.ch, "/2-") != NULL) { strncpy(dialog.character2, " ", 16); R_ResetPortraitAnim(); goto read; }
			else if (strstr(dialog.ch, "/3-") != NULL) { strncpy(dialog.character3, " ", 16); R_ResetPortraitAnim(); goto read; }

			else if (strstr(dialog.ch, "/=m=") != NULL) {

				char *head = strtok(dialog.ch, "; ");
				char *initbuf = (char*)malloc(sizeof(char) * 64);

				while (head != NULL) {

					if(strstr(head, "TEXT_1:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; menu.text1 = initbuf + 1; printf("TEXT_1: '%s'\n", menu.text1); }
					if(strstr(head, "TEXT_2:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; menu.text2 = initbuf + 1; printf("TEXT_2: '%s'\n", menu.text2); }
					if(strstr(head, "PATH_1:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; menu.path1 = initbuf + 1; printf("PATH_1: '%s'\n", menu.path1); }
					if(strstr(head, "PATH_2:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; menu.path2 = initbuf + 1; printf("PATH_2: '%s'\n", menu.path2); }

				//	printf("'%s'\n", head);
					head = strtok(NULL, ";");
				}	

				dialog.is_menu = true;
				free(head);

			}
 
			dialog.line_num++;
		}
	
		if (animplayer6 > 223 && animplayer7 > 223 && dialog.render_characters == true ) {
			/* character shit */
			if (strstr(dialog.character0, "CYGAR") != NULL || strstr(dialog.character1, "CYGAR") != NULL || strstr(dialog.character2, "CYGAR") != NULL || strstr(dialog.character3, "CYGAR") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "cygar_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "RURY") != NULL || strstr(dialog.character1, "RURY") != NULL || strstr(dialog.character2, "RURY") != NULL || strstr(dialog.character3, "RURY") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "rury_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "DONIX") != NULL || strstr(dialog.character1, "DONIX") != NULL || strstr(dialog.character2, "DONIX") != NULL || strstr(dialog.character3, "DONIX") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "donix_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "OTIS") != NULL || strstr(dialog.character1, "OTIS") != NULL || strstr(dialog.character2, "OTIS") != NULL || strstr(dialog.character3, "OTIS") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "otis_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "MCAT") != NULL || strstr(dialog.character1, "MCAT") != NULL || strstr(dialog.character2, "MCAT") != NULL || strstr(dialog.character3, "MCAT") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "mcat_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "KTOSIEK") != NULL || strstr(dialog.character1, "KTOSIEK") != NULL || strstr(dialog.character2, "KTOSIEK") != NULL || strstr(dialog.character3, "KTOSIEK") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "ktosiek_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "FLORYDA") != NULL || strstr(dialog.character1, "FLORYDA") != NULL || strstr(dialog.character2, "FLORYDA") != NULL || strstr(dialog.character3, "FLORYDA") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "floryda_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "JALAPENO") != NULL || strstr(dialog.character1, "JALAPENO") != NULL || strstr(dialog.character2, "JALAPENO") != NULL || strstr(dialog.character3, "JALAPENO") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "jalapeno_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "MISSINGNO") != NULL || strstr(dialog.character1, "MISSINGNO") != NULL || strstr(dialog.character2, "MISSINGNO") != NULL || strstr(dialog.character3, "MISSINGNO") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "missingno_sheet")); dialog.character_count++;
			} if (strstr(dialog.character0, "ABW") != NULL || strstr(dialog.character1, "ABW") != NULL || strstr(dialog.character2, "ABW") != NULL || strstr(dialog.character3, "ABW") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "glowie_sheet")); dialog.character_count++;
			} 



			dialog.character_count = 1;
		}

		/* the main dialog box */
		UI_FillRect(STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 72, GAME_VIEWPORT_WIDTH / UI_SCALE - 4, 72, true);
		UI_Rect(STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 72, GAME_VIEWPORT_WIDTH / UI_SCALE - 4, 72, true);

		/* the character name box */
		UI_FillRect(STANDARD_PADDING + 10, GAME_VIEWPORT_HEIGHT / UI_SCALE - 84, 72, 12, true);
		UI_Rect(STANDARD_PADDING + 10, GAME_VIEWPORT_HEIGHT / UI_SCALE - 84, 72, 12, true);

		/* the label */
		if (animplayer6 > 223 && animplayer7 > 223) {
			UI_TextLabelEx(2 + STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 72, 255, 255, 255, dialog.ch, GAME_VIEWPORT_WIDTH / UI_SCALE - STANDARD_PADDING, true);
			UI_TextLabelEx(10 + STANDARD_PADDING, GAME_VIEWPORT_HEIGHT / UI_SCALE - 84, 255, 255, 255, dialog.current_character, GAME_VIEWPORT_WIDTH / UI_SCALE - STANDARD_PADDING, true);
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
				UI_TextLabel(8, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), label_1, 244);
			} else {
				UI_TextLabel(8, (GAME_VIEWPORT_HEIGHT / UI_SCALE) - ((i + 1) * 35), label_2, 244);
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
