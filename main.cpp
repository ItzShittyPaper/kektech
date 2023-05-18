#include "libs.h"

#include "config.h"
#include "main.h"
#include "render.h"
#include "input.h"
#include "ui.h"
#include "map.h"

// definitions
dialog_file dialog;
dialog_menu menu;
player_ent  player;
modes       mode;

/* ANIMATION PLAYERS */
int animplayer0 = 0;
int animplayer1 = 0;
int animplayer2 = 0;
int animplayer3 = 0;
int animplayer4 = 0;
/* reserved for the player (and party) world animations */
int animplayer5 = 0;
/* reserved for ui animations */
int animplayer6 = 0;
int animplayer7 = 0;

// Pointers to our window, renderer, texture, and font
SDL_Rect dest;

/*

MISC FUNCTIONS

*/

void RNG_Init() {

	srand(time(0));	

}

int RNG_GenSeed(int rand_min, int rand_max) {

	int i;
	int num = (rand() %
	(rand_max - rand_min + 1)) + rand_min;
	std::cout << num << std::endl;
	return num;
}

void PLAYER_Init() {

	player.collider.x = 0;
	player.collider.y = 0;
	player.collider.w = 16;
	player.collider.h = 16;

}

void PLAYER_Move() {

	//Move the dot left or right
	player.pos_x += player.vel_x;
	player.collider.x = player.pos_x;
    
 	//Move the dot up or down
	player.pos_y += player.vel_y;
	player.collider.y = player.pos_y;

	/* stop and start the animation depending on the player movement */
	/* i know that i should use the || (OR) operator here, but it doesnt fucking work */
	if (player.vel_y != 0) { player.is_moving = 1; }
	else if (player.vel_x != 0) { player.is_moving = 1; }
	else { player.is_moving = 0; animplayer5 = 0; }
}

/* ============================= */

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
	SDL_RenderSetLogicalSize(renderer, game_screen_width / 2, game_screen_height / 2);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);	

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
				if (e.key.repeat == 0) {
					if (e.key.keysym.sym == SDLK_BACKSPACE && textbox_input.size()) {
						textbox_input.pop_back();
					} else {
						I_ProcessKeyDownEvent();
					}
				} break;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_BACKSPACE && textbox_input.size()) {
					textbox_input.pop_back();
				} else {
					I_ProcessKeyUpEvent();
				} break;
		}
	}

	PLAYER_Move();
	M_ReadMapFile("leo/ds/test.ds");
	R_DrawPlayer(leo_sheet, player.direction);
//	UI_Dialog("leo/txt/dialog0.txt");

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
	font = TTF_OpenFont("leo/res/ff1.ttf", 24);
	if ( !font ) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	// Start sending SDL_TextInput events
//	SDL_StartTextInput();
	
	// Initialize the random number generator
	RNG_Init();

	// Load Textures Into the Memory
	R_InitTextures();

	// Initialize the player entity
	PLAYER_Init();

	mode = main_mode;

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
