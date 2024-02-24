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

ui_button button;

#define RECT_R 0.0625f
#define RECT_G 0.5f
#define RECT_B 0.25f

#define RECTBG_R 0.0f
#define RECTBG_G 0.0f
#define RECTBG_B 0.0f

#define SELECT_RECT_R 64
#define SELECT_RECT_G 16
#define SELECT_RECT_B 128

#define BUTTON_TEXTGAP 4
#define BUTTON_FONTWIDTH 3
#define BUTTON_FONTHEIGHT 5

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

	SDL_Color foreground = { 255, 255, 255 };
	
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
	if (UI_log.logtextanimation < LOG_SHOW_LENGTH) {

		/* bruh */
		//UI_TextLabel(2, 2, text, game_screen_width);
		R_RenderText(fontshader, text, 2.0f * UI_SCALE, 2.0f * UI_SCALE, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
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
		SDL_SetRenderDrawColor(renderer, RECT_R, RECT_G, RECT_B, 255);
	} else {

		if (animplayer7 > 255) {
			animplayer7 = 255;
		}

		SDL_SetRenderDrawColor(renderer, RECT_R, RECT_G, RECT_B, 0 + animplayer7);
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
		SDL_SetRenderDrawColor(renderer, SELECT_RECT_R, SELECT_RECT_G, SELECT_RECT_B, 255);
	} else {

		if (animplayer7 > 255) {
			animplayer7 = 255;
		}

		SDL_SetRenderDrawColor(renderer, SELECT_RECT_R, SELECT_RECT_G, SELECT_RECT_B, 0 + animplayer7);
		animplayer7 = animplayer7 + 8;
	}

	SDL_RenderDrawRect(renderer, &rect);
	
}

void UI_SelectRectEx(int pos_x, int pos_y, int width, int height, uint8_t r, uint8_t g, uint8_t b, bool is_animated) {

//	animplayer7 = 0;

	SDL_Rect rect;
	rect.x = pos_x * UI_SCALE;
	rect.y = pos_y * UI_SCALE;
	rect.w = width * UI_SCALE;
	rect.h = height * UI_SCALE;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, r, g, b, 255);
	} else {

		if (animplayer7 > 255) {
			animplayer7 = 255;
		}

		SDL_SetRenderDrawColor(renderer, r, g, b, 0 + animplayer7);
		animplayer7 = animplayer7 + 8;
	}


	SDL_RenderDrawRect(renderer, &rect);
	
}

void UI_FillRect(float pos_x, float pos_y, float width, float height, bool is_animated) {

//	animplayer6 = 0;

	SDL_Rect rect;
	rect.x = pos_x * UI_SCALE;
	rect.y = pos_y * UI_SCALE;
	rect.w = width * UI_SCALE;
	rect.h = height * UI_SCALE;

	if (is_animated == false) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 224);
	} else {

		if (animplayer6 > 224) {
			animplayer6 = 224;
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
	rect.x = pos_x * UI_SCALE;
	rect.y = pos_y * UI_SCALE;
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

/* ----------------------------
	BUTTON CODE
*/

void UI_ExampleButtonCallback() { 
	printf("hello!!!!! :3\n");
}

void UI_ButtonCallback(void (*ptr)())
{
    (*ptr)(); /* callback to UI_ExampleButtonCallback() */
}

void UI_RenderButton(ui_button button, int rendermode) {
	if (rendermode != 0) {
		UI_FillRect(button.pos_x, button.pos_y, button.width, button.height, true);
		UI_SelectRect(button.pos_x, button.pos_y, button.width, button.height, true);
		goto rendertext;
	}
	if (rendermode == 0) {
		UI_FillRect(button.pos_x, button.pos_y, button.width, button.height, true);
		UI_Rect(button.pos_x, button.pos_y, button.width, button.height, true);
		goto rendertext;
	}

	rendertext:
	switch(button.textstyle) {

		case 0:
			UI_TextLabel(button.pos_x + BUTTON_TEXTGAP, button.pos_y + (button.height / 2) - BUTTON_FONTHEIGHT, button.title, button.width);
			R_RenderText(fontshader, button.title, (button.pos_x + BUTTON_TEXTGAP) * UI_SCALE, (button.pos_y + (button.height / 2) - BUTTON_FONTHEIGHT) * UI_SCALE, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			break;
		case 1:
			UI_TextLabel(button.pos_x + (button.width / 2) - (strlen(button.title) * BUTTON_FONTWIDTH), button.pos_y + (button.height / 2) - BUTTON_FONTHEIGHT, button.title, button.width);
			R_RenderText(fontshader, button.title, (button.pos_x + (button.width / 2) - (strlen(button.title)) * BUTTON_FONTWIDTH) * UI_SCALE, (button.pos_y + (button.height / 2) - BUTTON_FONTHEIGHT) * UI_SCALE, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			break;
	}
}

void UI_HandleButtonEvent(SDL_Event e, ui_button button) {

   	//The mouse offsets
    	int x = 0, y = 0;
	x = global_offset.x;
        y = global_offset.y;

	//If the mouse is over the button
        if ((x > button.pos_x) && (x < button.pos_x + button.width) && (y > button.pos_y - ((button.height / 2) * UI_SCALE)) && (y < button.pos_y + button.height)) {

		if( global_mousemasks_pressed.mouse_left == true ) {
				button.mode = 1;
        	}
		if( global_mousemasks_released.mouse_left == true) {
			//void *ptr = button.ptr;
			UI_ButtonCallback(button.ptr);
            	}
	}
	UI_RenderButton(button, button.mode);
}

void UI_Button(ui_button button) {
	
	UI_HandleButtonEvent(e, button);
}

void UI_WindowFrameEx(int pos_x, int pos_y, int width, int height, uint8_t r_bg, uint8_t g_bg, uint8_t b_bg, uint8_t r_text, uint8_t g_text, uint8_t b_text, const char* title) {

	int y_content_offset = 8;

	/* DRAW THE WINDOW ITSELF */
	UI_FillRectEx(pos_x, pos_y, width, height, r_bg, g_bg, b_bg, true);
	UI_SelectRectEx(pos_x, pos_y, width, height, r_text, g_text, b_text, true);
	UI_TextLabelEx(pos_x + 2, pos_y + 2, r_text, g_text, b_text, title, width, true);

}
