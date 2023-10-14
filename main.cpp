/* basic APIs */
#include "libs.h"

/* base kektech */
#include "main.h"
#include "render.h"
#include "audio.h"
#include "map.h"
#include "ui.h"
#include "input.h"
#include "save.h"

// definitions
dialog_file dialog;
dialog_menu menu;
player_ent  player;
modes       mode;
game_manager gamemgr;

/* ANIMATION PLAYERS */
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

const int game_viewport_width = 1280;
const int game_viewport_height = 720;

//Screen dimension constants
const int game_screen_width = game_viewport_width * RENDER_SCALE;
const int game_screen_height = game_viewport_height * RENDER_SCALE;

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

/* ======================== */

int main(int argc, char *argv[]) {

	if ( !init() ) {
		printf("KEKTECH FAILED TO START\nCHECK YOUR SDL LIBRARY AND CONTACT THE DISTRIBUTOR OF THE GAME\n");
		return 1;
	}

	if (argc == 2) {
		mode = main_mode;
		/* the limit is 128 - the prefix */
		snprintf(gamemgr.currentmap, 128, "%s/%s", "leo/ds", argv[1]);
	}

	while ( loop() ) {
		// wait before processing the next frame
		if (gamemgr.frame_deltatime > (1000 / TARGET_FPS)) { } else {
			SDL_Delay((1000 / TARGET_FPS) - gamemgr.frame_deltatime);
		}
	}

	kill();
	return 0;
}

// MAIN GAME LOOP
bool loop() {

	/*
		SETUP
	*/

	gamemgr.frame_starttime = SDL_GetTicks64();

	static const unsigned char* keys = SDL_GetKeyboardState( NULL );
	SDL_Rect dest;
	is_interacting = 0;

	SDL_RenderSetLogicalSize(renderer, game_viewport_width, game_viewport_height);
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
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_BACKSPACE && textbox_input.size()) {
					textbox_input.pop_back();
				} else if (gamemgr.is_paused == false) {
					I_ProcessKeyUpEvent();
				} break;
			case SDL_KEYDOWN:
				if (e.key.repeat == 0) {
					if (e.key.keysym.sym == SDLK_BACKSPACE && textbox_input.size()) {
						textbox_input.pop_back();
					} else if (gamemgr.is_paused == false) {
						I_ProcessPauseEvent();
						I_ProcessKeyDownEvent();
					} else {
						I_ProcessPauseEvent();
					}
				} break;
		}
	}

	A_MusicUpdateEvent();

	/* check if the player isn't in the game menu (dashboard) */
	/* this function is flexible, handling exceptions like the player not being alive etc. */
	if (mode < 250) {

		ClientGameLoop();

	}
	else {

		/* a switch for special modes that arent the main game */
		switch(mode) {

			/* loading transitions */
			case 252:

				ClientLoadingAnim();

				SDL_RenderCopy(renderer, UI_dashboard.menu_background, NULL, NULL);
				break;

			/* kkui_dashboard (game's main menu) */
			case 255:
				M_ReadMapFile("leo/ds/kkui_dashboard/dashboard.ds", texturemgr);
				UI_WindowFrameEx(6, 82, 240, 72, 0, 0, 0, 224, 112, 224, "WITAMY W DEMIE ZDS!!!");
				UI_TextLabelEx(8, 98, 224, 112, 224, "AKTUALIZACJA 1.0.2: SNAKE MINIGIERKA DOSTEPNA POD KLAWISZEM V, NOWA WERSJA SILNIKA, AKTUALIZACJE INTERFEJSU POD MASKA, OGOLNE POPRAWKI. DZIEKUJE ZA WSZELKIE WSPARCIE - m4kulatura", 238, true);
				UI_ShowLog(UI_log.logbuffer);	
				break;
			/* kkui_crash (the so called "NSOD" (nerd screen of death)) */
			case 254:
				UI_CrashScreen(UI_nsod.crash_logbuffer);
				break;
			/* kkui_credit (the credits screen showed at the end of the game) */
			case 253:
				M_ReadMapFile(gamemgr.currentmap, texturemgr);
				break;
		}
	}

	/*
		PAUSE CHECK
	*/

	if (gamemgr.is_paused == true) {
		UI_FillRectEx(2, game_viewport_height / UI_SCALE - 20, game_viewport_width / UI_SCALE, 20, 255, 255, 255, true);
		UI_TextLabelEx(2,  game_viewport_height / UI_SCALE / 2 - 20 / UI_SCALE, 0, 0, 0, "THE GAME IS PAUSED, PRESS F10 TO RESUME IT\nWARNING: MOVING WHILE PAUSED CAN CAUSE ISSUES", game_viewport_width / UI_SCALE, true);
	}

	/* UPDATE WINDOW AT THE END */
	SDL_RenderPresent(renderer);

	/*
		WRAP-UP
	*/

	gamemgr.frame_endtime = SDL_GetTicks64();
	gamemgr.frame_deltatime = gamemgr.frame_endtime - gamemgr.frame_starttime;

	/* do nothing if you're in the menu */
	return true;

}

bool init() {

	/* allocate the crash log buffer so windows doesnt complain when shit inevitably fucks itself (:3) */
	UI_nsod.crash_logbuffer = (char*)malloc(1024 * sizeof(char*));

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

	/* load the font data */
	font = TTF_OpenFont("leo/res/slkscr.ttf", 8);
	if ( !font ) {
		snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING FONT, FILE DOES NOT EXIST / PERMISSION DENIED"); mode = kkui_crash; return false;
	}

	//Initialize SDL_mixer
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ) {
		snprintf(UI_nsod.crash_logbuffer, 256, "ERROR INITIALIZING AUDIO, YOUR SOUND CARD / DRIVER MIGHT NOT WORK"); mode = kkui_crash; return false;
	}	

	// initialize texture manager - tijon
	texturemgr = new game_texture();
	texturemgr->cachedMaterials = std::vector<MaterialDefinition*>();

	sfxmgr = new game_sfx();
	sfxmgr->cachedSounds = std::vector<SoundDefinition*>();

	/* start sending SDL_TextInput events */
//	SDL_StartTextInput();

	//dialog.is_menu = false;

	UI_InitLog();
	/* initialize the random number generator */
	RNG_Init();

	/* load textures and sound effects into our memory */
	R_InitTextures(texturemgr);
	A_InitSoundEffects(sfxmgr);
	/* initialize the player entity */
//	PLAYER_Init();

	mode = kkui_dashboard;
	strcpy(gamemgr.currentmap, "leo/ds/start.ds");

	//SAVE_InitSaveOperation();
	//SAVE_WriteKeyToFile("omg", "haii");
	//SAVE_ReadKeyFromFile();

	ClientInit();

	/* you HAVE to send something, for some reason. will move to UI_InitLog() because of that */
	UI_SendLog(" ");

	return true;
}

void kill() {
	R_FreeMaterial(texturemgr);

	SDL_StopTextInput();

	free(UI_nsod.crash_logbuffer);

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
