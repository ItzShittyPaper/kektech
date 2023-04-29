#include "libs.h"
#include "render.h"
#include "ui.h"
#include "main.h"

std::string textbox_input;
game_ui UI;

// Pointers to our window, renderer, texture, and font

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

	SDL_Color foreground = { 255, 255, 255 };
	
	SDL_Surface* text_surf = TTF_RenderText_Solid_Wrapped(font, label, foreground, wrap_length);

	UI.text = SDL_CreateTextureFromSurface(renderer, text_surf);
	dest.x = pos_x;
	dest.y = pos_y;
	dest.w = text_surf->w;
	dest.h = text_surf->h;
	SDL_RenderCopy(renderer, UI.text, NULL, &dest);

	SDL_DestroyTexture(UI.text);
	SDL_FreeSurface(text_surf);

}

void UI_Rect(int pos_x, int pos_y, int width, int height, bool is_animated) {

//	animplayer7 = 0;

	SDL_Rect rect;
	rect.x = pos_x;
	rect.y = pos_y;
	rect.w = width;
	rect.h = height;

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
	rect.x = pos_x;
	rect.y = pos_y;
	rect.w = width;
	rect.h = height;

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
	rect.x = pos_x;
	rect.y = pos_y;
	rect.w = width;
	rect.h = height;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	} else {

		if (animplayer6 > 255) {
			animplayer6 = 255;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0 + animplayer6);
		animplayer6 = animplayer6 + 8;
	}

	SDL_RenderFillRect(renderer, &rect);
	
}

void UI_DialogBox(bool is_animated, const char* file, const char* text_id) {

	if (mode == dialog_mode) {

		/* animation code */
		if (is_animated == true) {
			UI_FillRect(4, 212, 312, 72, true);
			UI_Rect(4, 212, 312, 72, true);
		} else {
			UI_FillRect(4, 212, 312, 72, false);
			UI_Rect(4, 212, 312, 72, false);
		}

		/* displaying the text after finishing the animation */
		if (animplayer6 > 256 && animplayer7 > 256) {

			if (dialog.is_triggered == false) {

				mode = dialog_mode;
				dialog.target_num = 1;
				dialog.line_num = 1;
				dialog.ptr = fopen(file, "r");

				dialog.is_triggered = true;

			}

			for (dialog.line_num; dialog.line_num <= dialog.target_num; dialog.line_num++) {

				fgets(dialog.ch, sizeof(dialog.ch), dialog.ptr);

				/* CHECK FOR DIALOG END */
				dialog.tag = strstr(dialog.ch, "#=#");
				if (dialog.tag != NULL) { fclose(dialog.ptr); mode = main_mode; break; }

			}

			R_DrawCharacterPortrait(244, 212, leo_sheet);
			UI_TextLabel(8, 214, dialog.ch, 244);
//			UI_TextLabel(8, 214, "hellodsadasd", 244);
		}
	}
}

char* UI_Menu(bool is_animated, const char* label_1, const char* label_2, const char* path_1, const char* path_2) {

	if (mode == dialog_mode) {

		/* animated rectangle code */
		if (is_animated == true) {
			UI_FillRect(4, 212, 312, 72, true);
			UI_Rect(4, 212, 312, 72, true);
		} else {
			UI_FillRect(4, 212, 312, 72, false);
			UI_Rect(4, 212, 312, 72, false);
		}

		if (menu.option > 1)
			menu.option = 0;
		else if (menu.option < 0)
			menu.option = 0;
		
		/* check for selection */
		if (menu.is_selected == 1) {
			switch (menu.option) {

				case 0:
					printf("%s\n", path_1);
					dialog.is_menu = 0;
					return (char*)path_1;
					break;
				case 1:
					printf("%s\n", path_2);
					dialog.is_menu = 0;
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
}

void UI_Dialog(char* buffer) {

	if (dialog.is_menu == 0) {
		UI_DialogBox(true, dialog.file_buffer, "LEO");
	}

	if (dialog.is_menu == 1) {
		dialog.file_buffer = UI_Menu(true, "h", "not h", "leo/txt/menu_test/dialog1.txt", "leo/txt/menu_test/dialog2.txt");
	}

}
