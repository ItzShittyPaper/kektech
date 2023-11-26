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

void UI_RenderButton(ui_button button) {

	UI_FillRect(button.pos_x, button.pos_y, button.width, button.height, true);
	UI_Rect(button.pos_x, button.pos_y, button.width, button.height, true);
	UI_TextLabel(button.pos_x + (button.width / 2) - (strlen("epic gaming") * 3), button.pos_y + (button.height / 2), "epic gaming", 144);

}

void UI_RenderSelectButton(ui_button button) {

	UI_FillRect(button.pos_x, button.pos_y, button.width, button.height, true);
	UI_SelectRect(button.pos_x, button.pos_y, button.width, button.height, true);
	UI_TextLabel(button.pos_x + (button.width / 2) - (strlen("epic gaming") * 3), button.pos_y + (button.height / 2), "epic gaming", 144);

}

void UI_HandleButtonEvent(SDL_Event e, ui_button button) {

	button.pos_x = 0;
	button.pos_y = 0;
	button.width = 128;
	button.height = 128;
    

   //The mouse offsets
    int x = 0, y = 0;

    while (SDL_PollEvent(&e) != 0) {
	// process events
		switch (e.type) {
    			case SDL_MOUSEMOTION:
   				x = global_offset.x;
        			y = global_offset.y;
        
        			//If the mouse is over the button
        			if( ( x > button.pos_x ) && ( x < button.pos_x + button.width ) && ( y > button.pos_y ) && ( y < button.pos_y + button.height ) ) {
					UI_RenderButton(button);
        			}
				continue;

    			//If a mouse button was pressed
    			case SDL_MOUSEBUTTONDOWN:
        			//If the left mouse button was pressed
        			if( e.button.button == SDL_BUTTON_LEFT ) {
            				//Get the mouse offsets
            				x = e.button.x;
            				y = e.button.y;
        
            				//If the mouse is over the button
            				if( ( x > button.pos_x ) && ( x < button.pos_x + button.width ) && ( y > button.pos_y ) && ( y < button.pos_y + button.height ) ) {
						UI_RenderSelectButton(button);
						printf("sex\n");
            				}
        			}
    				continue;	

    			//If a mouse button was released
    			case SDL_MOUSEBUTTONUP:
        			//If the left mouse button was released
        			if( e.button.button == SDL_BUTTON_LEFT ) { 
            				//Get the mouse offsets
            				x = e.button.x;
            				y = e.button.y;
        		
            				//If the mouse is over the button
            				if( ( x > button.pos_x ) && ( x < button.pos_x + button.width ) && ( y > button.pos_y ) && ( y < button.pos_y + button.height ) ) {
						UI_RenderButton(button);
						void (*ptr)() = &UI_ExampleButtonCallback;
						UI_ButtonCallback(ptr);
            				}
        			}
    		}
	}		
}

void UI_Button(ui_button button) {
	
	button.pos_x = 0;
	button.pos_y = 0;
	button.width = 128;
	button.height = 128;
    
	UI_HandleButtonEvent(e, button);
	UI_RenderButton(button);

}

void UI_WindowFrameEx(int pos_x, int pos_y, int width, int height, uint8_t r_bg, uint8_t g_bg, uint8_t b_bg, uint8_t r_text, uint8_t g_text, uint8_t b_text, const char* title) {

	int y_content_offset = 8;

	/* DRAW THE WINDOW ITSELF */
	UI_FillRectEx(pos_x, pos_y, width, height, r_bg, g_bg, b_bg, true);
	UI_SelectRectEx(pos_x, pos_y, width, height, r_text, g_text, b_text, true);
	UI_TextLabelEx(pos_x + 2, pos_y + 2, r_text, g_text, b_text, title, width, true);

}
