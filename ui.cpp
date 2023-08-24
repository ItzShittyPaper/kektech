#include "libs.h"
#include "render.h"
#include "ui.h"
#include "main.h"

std::string textbox_input;
game_ui UI;
ui_log UI_log;
ui_dashboard UI_dashboard;
ui_nsod UI_nsod;
ui_rgbcolor UI_rgbcolor;

// Pointers to our window, renderer, texture, and font

ui_rgbcolor UI_RGBColorReturn(char* chunk) {

	ui_rgbcolor rgb;

	char *head = strtok(chunk, "; ");
	char *rgbbuf = (char*)malloc(sizeof(char) * 64);

	while (head != NULL) {

		if(strstr(head, "RED:") != NULL) { rgbbuf = strchr( head, ':' ); rgb.r = atoi(rgbbuf + 1); }
		if(strstr(head, "GREEN:") != NULL) { rgbbuf = strchr( head, ':' ); rgb.g = atoi(rgbbuf + 1); }
		if(strstr(head, "BLUE:") != NULL) { rgbbuf = strchr( head, ':' ); rgb.b = atoi(rgbbuf + 1); }

		//printf("'%s'\n", head);

		head = strtok(NULL, ";");
	}

	//free(rgbbuf);
	return rgb;

}

void UI_TextBox() {

	SDL_Color foreground = { 255, 255, 255 };
	
	if ( textbox_input.size() ) {
		SDL_Surface* text_surf = TTF_RenderText_Solid(font, textbox_input.c_str(), foreground);

		UI.text = SDL_CreateTextureFromSurface(renderer, text_surf);
		dest.x = 320 - (text_surf->w / 2.0f);
		dest.y = 240;
		dest.w = text_surf->w;
		dest.h = text_surf->h;
		SDL_RenderCopy(renderer, UI.text, NULL, &dest);

		SDL_DestroyTexture(UI.text);
		SDL_FreeSurface(text_surf);
	}
}

void UI_TextLabel(int pos_x, int pos_y, const char *label, int wrap_length) {

	SDL_Color foreground = { 255, 0, 255 };
	
	SDL_Surface* text_surf = TTF_RenderText_Solid_Wrapped(font, label, foreground, wrap_length);

	UI.text = SDL_CreateTextureFromSurface(renderer, text_surf);
	dest.x = pos_x * UI_SCALE;
	dest.y = pos_y * UI_SCALE;
	dest.w = text_surf->w * UI_SCALE;
	dest.h = text_surf->h * UI_SCALE;

	SDL_RenderCopy(renderer, UI.text, NULL, &dest);

	SDL_DestroyTexture(UI.text);
	SDL_FreeSurface(text_surf);

}

void UI_TextLabelEx(int pos_x, int pos_y, uint8_t r, uint8_t g, uint8_t b, const char *label, int wrap_length, bool is_scaled) {

	SDL_Color foreground = { r, g, b };
	
	SDL_Surface* text_surf = TTF_RenderText_Solid_Wrapped(font, label, foreground, wrap_length);

	UI.text = SDL_CreateTextureFromSurface(renderer, text_surf);

	if (is_scaled == true) {
		dest.x = pos_x * UI_SCALE;
		dest.y = pos_y * UI_SCALE;
		dest.w = text_surf->w * UI_SCALE;
		dest.h = text_surf->h * UI_SCALE;
	} else {
		dest.x = pos_x;
		dest.y = pos_y;
		dest.w = text_surf->w;
		dest.h = text_surf->h;
	}

	SDL_RenderCopy(renderer, UI.text, NULL, &dest);

	SDL_DestroyTexture(UI.text);
	SDL_FreeSurface(text_surf);

}

void UI_ConstructLogBuffer() {

	UI_log.logbuffer = (char*)malloc(sizeof(char) * 8192);

	std::string log0;
	std::string log1;
	std::string log2;
	std::string log3;

	log0 = UI_log.log_vector.at(0);
	log1 = UI_log.log_vector.at(1);
	log2 = UI_log.log_vector.at(2);
	log3 = UI_log.log_vector.at(3);

	if (!log0.empty()) { log0 += "\n"; std::cout << "A FUCKING LOG DEBUG: " << log0; }
	if (!log1.empty()) { log1 += "\n"; std::cout << "A FUCKING LOG DEBUG: " << log1; }
	if (!log2.empty()) { log2 += "\n"; std::cout << "A FUCKING LOG DEBUG: " << log2; }
	if (!log3.empty()) { log3 += "\n"; std::cout << "A FUCKING LOG DEBUG: " << log3; }

	std::snprintf(UI_log.logbuffer, 8192, "%s%s%s%s", log0.c_str(), log1.c_str(), log2.c_str(), log3.c_str());

	//std::cout << UI_log.logbuffer;

}

void UI_SendLog(const char* text) {

	/* reset the fadeout */
	UI_log.logtextanimation = 0;

	UI_log.log_vector.insert(UI_log.log_vector.begin() + UI_log.ioffset, (char*)text);
	UI_log.ioffset++;
	if (UI_log.ioffset < 4) {
		UI_log.ioffset = 0;
	}

	UI_ConstructLogBuffer();

}

void UI_InitLog() {

	UI_log.log_vector.resize(4);
	UI_log.ioffset = 0;

//	UI_SendLog("this is a log test");
	//UI_SendLog("log test 3");
	//UI_SendLog("log test 4");
	//UI_SendLog("log test 5");

	UI_ConstructLogBuffer();

	//for (int i = 0; i < UI_log.log_vector.size(); i++) {
	//	std::cout << UI_log.log_vector.at(i) << ' ' << std::endl;
	//}


}

void UI_ShowLog(const char* text) {
	if (UI_log.logtextanimation < 72) {

		/* bruh */
		UI_TextLabel(2, 2, text, game_screen_width);
		UI_log.logtextanimation++;

	}
}

void UI_Rect(int pos_x, int pos_y, int width, int height, bool is_animated) {

//	animplayer7 = 0;

	SDL_Rect rect;
	rect.x = pos_x * UI_SCALE;
	rect.y = pos_y * UI_SCALE;
	rect.w = width * UI_SCALE;
	rect.h = height * UI_SCALE;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 128, 255);
	} else {

		if (animplayer7 > 255) {
			animplayer7 = 255;
		}

		SDL_SetRenderDrawColor(renderer, 0, 255, 128, 0 + animplayer7);
		animplayer7 = animplayer7 + 8;
	}

	SDL_RenderDrawRect(renderer, &rect);
	
}

void UI_SelectRect(int pos_x, int pos_y, int width, int height, bool is_animated) {

//	animplayer7 = 0;

	SDL_Rect rect;
	rect.x = pos_x * UI_SCALE;
	rect.y = pos_y * UI_SCALE;
	rect.w = width * UI_SCALE;
	rect.h = height * UI_SCALE;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	} else {

		if (animplayer7 > 255) {
			animplayer7 = 255;
		}

		SDL_SetRenderDrawColor(renderer, 0, 255, 255, 0 + animplayer7);
		animplayer7 = animplayer7 + 8;
	}

	SDL_RenderDrawRect(renderer, &rect);
	
}

void UI_FillRect(int pos_x, int pos_y, int width, int height, bool is_animated) {

//	animplayer6 = 0;

	SDL_Rect rect;
	rect.x = pos_x * UI_SCALE;
	rect.y = pos_y * UI_SCALE;
	rect.w = width * UI_SCALE;
	rect.h = height * UI_SCALE;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 224);
	} else {

		if (animplayer6 > 255) {
			animplayer6 = 255;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0 + animplayer6);
		animplayer6 = animplayer6 + 8;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);
	
}

void UI_FillRectEx(int pos_x, int pos_y, int width, int height, uint8_t r, uint8_t g, uint8_t b, bool is_animated) {

//	animplayer6 = 0;

	SDL_Rect rect;
	rect.x = pos_x;
	rect.y = pos_y;
	rect.w = width * UI_SCALE;
	rect.h = height * UI_SCALE;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, r, g, b, 224);
	} else {

		if (animplayer6 > 255) {
			animplayer6 = 255;
		}

		SDL_SetRenderDrawColor(renderer, r, g, b, 0 + animplayer6);
		animplayer6 = animplayer6 + 8;
	}

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);
	
}

void UI_CrashScreen(const char *label) {

	char* crashbuf = (char*)malloc(sizeof(char) * 4096);
	strcpy(crashbuf, "KEKTECH's NERD SCREEN OF DEATH\nsee the logs below for more information\n==========================================\n\n");
	strcat(crashbuf, label);

	SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255);

	SDL_RenderFillRect(renderer, NULL);
	UI_TextLabel(2, 2, crashbuf, game_screen_width);

	free(crashbuf);

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
				strncpy(dialog.character0, dialog.ch, 64);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 64);

				R_ResetPortraitAnim();
				goto read;
			} 
			else if (strstr(dialog.ch, "/1#") != NULL) {
				strncpy(dialog.character1, dialog.ch, 64);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 64);

				R_ResetPortraitAnim();
				goto read;
			}
			else if (strstr(dialog.ch, "/2#") != NULL) {
				strncpy(dialog.character2, dialog.ch, 64);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 64);

				R_ResetPortraitAnim();
				goto read;
			} 
			else if (strstr(dialog.ch, "/3#") != NULL) {
				strncpy(dialog.character3, dialog.ch, 64);
				strncpy(dialog.current_character, strchr(dialog.ch, ' '), 64);

				R_ResetPortraitAnim();
				goto read;
			} 

			else if (strstr(dialog.ch, "/0-") != NULL) { strncpy(dialog.character0, " ", 64); goto read; }
			else if (strstr(dialog.ch, "/1-") != NULL) { strncpy(dialog.character1, " ", 64); goto read; }
			else if (strstr(dialog.ch, "/2-") != NULL) { strncpy(dialog.character2, " ", 64); goto read; }
			else if (strstr(dialog.ch, "/3-") != NULL) { strncpy(dialog.character3, " ", 64); goto read; }

			else if (strstr(dialog.ch, "/=m=") != NULL) {

				char *head = strtok(dialog.ch, "; ");
				char *initbuf = (char*)malloc(sizeof(char) * 64);

				while (head != NULL) {

					if(strstr(head, "BACKGROUND:") != NULL) { initbuf = strchr( head, ':' ); initbuf[strcspn(initbuf, "\n")] = 0; UI_dashboard.menu_background = IMG_LoadTexture(renderer, initbuf + 1); printf("%s\n", initbuf + 1); }

					printf("'%s'\n", head);
					head = strtok(NULL, ";");
				}	

				free(head);
				goto read;

			}
 
			dialog.line_num++;
		}
	
		if (animplayer6 > 254 && animplayer7 > 254 && dialog.render_characters == true ) {
			/* character shit */
			if (strstr(dialog.character0, "CYGAR") != NULL || strstr(dialog.character1, "CYGAR") != NULL || strstr(dialog.character2, "CYGAR") != NULL || strstr(dialog.character3, "CYGAR") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "cygar_sheet")); dialog.character_count++;
			}
			if (strstr(dialog.character0, "RURY") != NULL || strstr(dialog.character1, "RURY") != NULL || strstr(dialog.character2, "RURY") != NULL || strstr(dialog.character3, "RURY") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "rury_sheet")); dialog.character_count++;
			}
			if (strstr(dialog.character0, "DONIX") != NULL || strstr(dialog.character1, "DONIX") != NULL || strstr(dialog.character2, "DONIX") != NULL || strstr(dialog.character3, "DONIX") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "donix_sheet")); dialog.character_count++;
			}
			if (strstr(dialog.character0, "OTIS") != NULL || strstr(dialog.character1, "OTIS") != NULL || strstr(dialog.character2, "OTIS") != NULL || strstr(dialog.character3, "OTIS") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "otis_sheet")); dialog.character_count++;
			}
			if (strstr(dialog.character0, "MCAT") != NULL || strstr(dialog.character1, "MCAT") != NULL || strstr(dialog.character2, "MCAT") != NULL || strstr(dialog.character3, "MCAT") != NULL) {
				R_DrawCharacterPortrait(R_GetMaterial(texturemgr, "mcat_sheet")); dialog.character_count++;
			}

			dialog.character_count = 1;
		}

		/* the main dialog box */
		UI_FillRect(STANDARD_PADDING, game_viewport_height / UI_SCALE - 72, game_viewport_width / UI_SCALE - 4, 72, true);
		UI_Rect(STANDARD_PADDING, game_viewport_height / UI_SCALE - 72, game_viewport_width / UI_SCALE - 4, 72, true);

		/* the character name box */
		UI_FillRect(STANDARD_PADDING + 10, game_viewport_height / UI_SCALE - 84, 72, 12, true);
		UI_Rect(STANDARD_PADDING + 10, game_viewport_height / UI_SCALE - 84, 72, 12, true);

		/* the label */
		if (animplayer6 > 254 && animplayer7 > 254) {
			UI_TextLabelEx(2 + STANDARD_PADDING, game_viewport_height / UI_SCALE - 72, 255, 255, 255, dialog.ch, game_viewport_width / UI_SCALE - STANDARD_PADDING, true);
			UI_TextLabelEx(10 + STANDARD_PADDING, game_viewport_height / UI_SCALE - 84, 255, 255, 255, dialog.current_character, game_viewport_width / UI_SCALE - STANDARD_PADDING, true);
		}
	}
	return 0;
}

char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2) {

	if (mode == dialog_mode) {

		PLAYER_ResetVel();
		/* animated rectangle code */
		UI_FillRect(STANDARD_PADDING, game_viewport_height / UI_SCALE - 72, game_viewport_width / UI_SCALE - 4, 72, true);
		UI_Rect(STANDARD_PADDING, game_viewport_height / UI_SCALE - 72, game_viewport_width / UI_SCALE - 4, 72, true);

		if (menu.option > 1)
			menu.option = 0;
		else if (menu.option < 0)
			menu.option = 0;
		
		/* check for selection */
		if (menu.is_selected == 1) {
			switch (menu.option) {

				case 0:
					printf("%s\n", path_1);
					dialog.is_menu = false;
					return (char*)path_1;
					break;
				case 1:
					printf("%s\n", path_2);
					dialog.is_menu = false;
					return (char*)path_2;
					break;
				default:
					printf("uhmmm wtf\n");
					exit(1);
			}
		}

		/* displaying the text after finishing the animation */
		if (animplayer6 > 256 && animplayer7 > 256) {
			for (int i = 0; i < 2; i++) {
				UI_FillRect(6, 214 + i * 35, 308, 33, false);

				if (i == menu.option) { UI_SelectRect(6, 214 + i * 35, 308, 33, false); }
				else { UI_Rect(6, 214 + i * 35, 308, 33, false); }
				
				if (i == 0) {
					UI_TextLabel(8, 214, label_1, 244);
				} else {
					UI_TextLabel(8, 214 + i * 35, label_2, 244);
				}
			}
		}
	}

	return NULL;

}

void UI_Dialog(char* buffer) {

	PLAYER_ResetVel();

	if (dialog.is_menu == true) {
		dialog.current_dialog = UI_Menu(true, "h", "not h", "leo/txt/menu_test/dialog1.txt", "leo/txt/menu_test/dialog2.txt");
	}
	else {
		UI_DialogBox(true, dialog.current_dialog);
	}
}
