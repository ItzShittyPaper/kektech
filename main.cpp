#include "libs.h"

#include "main.h"
#include "render.h"
#include "input.h"
#include "ui.h"
#include "map.h"
#include "render.h"

// definitions
dialog_file dialog;
dialog_menu menu;
player_ent  player;
modes       mode;
game_manager gamemgr;
audio_arch mixer;
game_texture* texturemgr;

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

/* interact check */
int is_interacting = 0;

// game-specific variables
const char *game_name = "silly funny game";
const char *game_version = "1.0";
const char *game_creator = "sexo";
const char *game_info = "a kektech game";
const char *game_url = "https://makulaturka.tk";

//Screen dimension constants
const int game_screen_width = 512;
const int game_screen_height = 448;

// Pointers to our window, renderer, texture, and font
SDL_Rect dest;

/*

MISC FUNCTIONS

*/

int A_AudioUpdateEvent() {

	//If there is no music playing
	if( Mix_PlayingMusic() == 0 ) {
		//Play the music
		Mix_PlayMusic( mixer.music, -1 );
	}
	return 0;
}

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

void PLAYER_ResetVel() {

	player.is_moving = 0;
	player.vel_y = 0;
	player.vel_x = 0;

}

void NPC_HelperActivate(SDL_Rect player_collider, SDL_Rect tile, char* dialog_path) {

	if (M_CheckCollision(player_collider, tile) && is_interacting == 1) {

		dialog.current_dialog = dialog_path;
		mode = dialog_mode;
//		printf("sexo\n");

	}

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

	/*
		SETUP
	*/

	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	SDL_Rect dest;
	is_interacting = 0;

	SDL_RenderSetLogicalSize(renderer, game_screen_width / 2, game_screen_height / 2);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);	
	R_Clear();

	/* ------------------------- */

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

	/* check if the player isn't in the game menu (dashboard) */
	/* this function is flexible, handling exceptions like the player not being alive etc. */
	if (mode != kkui_dashboard && mode != kkui_crash) {
		/*
			GAME LOGIC
		*/

		if (player.is_alive == true)
			PLAYER_Move();
		A_AudioUpdateEvent();

		/* ------------------------- */

		/*
			DRAWING
		*/

		//printf("%s\n", gamemgr.currentmap);
		M_ReadMapFile(gamemgr.currentmap, texturemgr);

		if (player.is_alive == true)
			R_DrawPlayer(leo_sheet, player.direction);

		//NPC_DrawEntity(zlew_sheet, 128, 64, 2, "leo/txt/dialog0.txt", 0);

		/* ------------------------- */

		/*
			UI
		*/

		/* show the game log on the top-left */
		UI_ShowLog(UI_log.logbuffer);

		/* mode checks i guess */
		UI_DialogBox(true, dialog.current_dialog);

		/* ------------------------ */
		
		// Update window
		SDL_RenderPresent(renderer);

		return true;
	}
	else {

		/* a switch for special modes that arent the main game */
		switch(mode) {

			/* kkui_dashboard (game's main menu) */
			case 255:
				SDL_RenderCopy(renderer, UI_dashboard.menu_background, NULL, NULL);

			//	UI_SendLog("the menu");
				UI_ShowLog(UI_log.logbuffer);	

				SDL_RenderPresent(renderer);
				break;
			/* kkui_crash (the so called "NSOD" (nerd screen of death)) */
			case 254:
				UI_nsod.crash_logbuffer = "Oh hewwo! So, back in 1963, a vewy important event happened. It was the assassination of JFK, which stands fow John F. Kennedy. Owo. On November 22nd, JFK was in Dawwas, Texas, attending a motorcade, which is like a pwocession in a car. Suddenly, a man named Lee Harvey Oswald shot him while he was riding in a convertible. It was a vewy sad day fow the United States and the wowld. o(TwTo)o JFK was the 35th Pwesident of the United States, and he was loved by many people. His death caused a wave of shock and gweat sadness. Investigations took place to find out who was wesponsible fow the assassination. Lee Harvey Oswald, the man who shot JFK, was later captured but was killed two days after the assassination, so he could not be twied in couwt. There awe still debates and conspiracy theories suwounding the events of that day, but it wemains a twagic moment in histowy. The assassination of JFK had a pwofound impact on the United States and the wowld. It changed the course of histowy and left a lasting legacy. It will always be wemembered as a significant event in the lives of many people. uwu";
				UI_CrashScreen(UI_nsod.crash_logbuffer);
				SDL_RenderPresent(renderer);
				break;

		}

	}

	/* do nothing if you're in the menu */
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

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
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

	/* load the font data */
	font = TTF_OpenFont("leo/res/slkscr.ttf", 8);
	if ( !font ) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
		return false;
	}

	// initialize texture manager - tijon
	texturemgr = new game_texture();
	texturemgr->cachedMaterials = std::vector<MaterialDefinition*>();
	/* start sending SDL_TextInput events */
//	SDL_StartTextInput();

	UI_InitLog();
	
	/* initialize the random number generator */
	RNG_Init();

	/* load textures into the memory */
	R_InitTextures(texturemgr);
	UI_dashboard.menu_background = IMG_LoadTexture(renderer, "leo/res/bg.png");

	/* initialize the player entity */
	PLAYER_Init();

	//mode = kkui_dashboard;
	mode = kkui_dashboard;
	strcpy(gamemgr.currentmap, "leo/ds/test.ds");

	UI_SendLog("Welcome to ze game!");
	return true;
}

void kill() {
	R_FreeMaterial(texturemgr);

	SDL_StopTextInput();

	//Free the music
	Mix_FreeMusic(mixer.music);
	mixer.music = NULL;	

	TTF_CloseFont( font );
	SDL_DestroyTexture( texture );
	texture = NULL;

	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	Mix_Quit();	
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
