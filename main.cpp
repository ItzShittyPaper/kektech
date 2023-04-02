#include "libs.h"

#include "config.h"
#include "main.h"
#include "render.h"
#include "input.h"
#include "ui.h"
#include "map.h"

// Pointers to our window, renderer, texture, and font

struct ui {

	SDL_Texture *text;

};

ui UI;
SDL_Rect dest;

void TextBox() {

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

void TextLabel(int pos_x, int pos_y, const char *label) {

	SDL_Color foreground = { 0, 0, 0 };
	
	SDL_Surface* text_surf = TTF_RenderText_Solid(font, label, foreground);

	UI.text = SDL_CreateTextureFromSurface(renderer, text_surf);
	dest.x = pos_x;
	dest.y = pos_y;
	dest.w = text_surf->w;
	dest.h = text_surf->h;
	SDL_RenderCopy(renderer, UI.text, NULL, &dest);

	SDL_DestroyTexture(UI.text);
	SDL_FreeSurface(text_surf);

}

void Rectangle(int pos_x, int pos_y, int width, int height) {

	SDL_Rect* rect_rect;
	SDL_RenderDrawRect(renderer, rect_rect);
	free(rect_rect);
	
}

int main(int argc, char** args) {

	if ( !init() ) {
		system("pause");
		return 1;
	}

	while ( loop() ) {
		// wait before processing the next frame
		SDL_Delay(10); 
	}

	kill();
	return 0;
}

// MAIN GAME LOOP
bool loop() {

	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	SDL_Rect dest;

	R_Clear();

	// Event loop
	while ( SDL_PollEvent( &e ) != 0 ) {

		// process events
		switch (e.type) {
			case SDL_QUIT:
				return false;
			case SDL_TEXTINPUT:
				textbox_input += e.text.text;
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_BACKSPACE && textbox_input.size()) {
					textbox_input.pop_back();
				}
				
				else {

					I_ProcessKeys();

				}
				break;
		}
	}

	M_DrawTileRect(1, 1, 6, 4, 16, glaggle);
	TextLabel(8, 8, "label widget test");

	// Render texture
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	//TextBox();

	// Update window
	SDL_RenderPresent( renderer );

	return true;
}

bool init() {
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return false;
	} 

	if ( IMG_Init(IMG_INIT_PNG) < 0 ) {
		std::cout << "Error initializing SDL_image: " << IMG_GetError() << std::endl;
		return false;
	}

	// Initialize SDL_ttf
	if ( TTF_Init() < 0 ) {
		std::cout << "Error intializing SDL_ttf: " << TTF_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow( game_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game_screen_width, game_screen_height, SDL_WINDOW_SHOWN );
	if ( !window ) {
		std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if ( !renderer ) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_Surface* buffer = IMG_Load("leo/bmp/leadpipe.png");
	if ( !buffer ) {
		std::cout << "Error loading image leadpipe.png: " << SDL_GetError() << std::endl;
		return false;
	}

	texture = SDL_CreateTextureFromSurface( renderer, buffer );
	SDL_FreeSurface( buffer );
	buffer = NULL;
	if ( !texture ) {
		std::cout << "Error creating texture: " << SDL_GetError() << std::endl;
		return false;
	}

	// Load font
	font = TTF_OpenFont("leo/res/tewi.ttf", 24);
	if ( !font ) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	// Start sending SDL_TextInput events
	SDL_StartTextInput();
	
	// Load Textures Into the Memory
	R_InitTextures();

	return true;
}

void kill() {
	SDL_StopTextInput();

	TTF_CloseFont( font );
	SDL_DestroyTexture( texture );
	texture = NULL;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
