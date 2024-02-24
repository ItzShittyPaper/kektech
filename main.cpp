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

#include "client/dialog.h"

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

//Screen dimension constants
const int game_screen_width = GAME_VIEWPORT_WIDTH * RENDER_SCALE;
const int game_screen_height = GAME_VIEWPORT_HEIGHT * RENDER_SCALE;

// Pointers to our window, renderer, texture, and font
SDL_Rect dest;

gl_texture texture1;
gl_texture texture2;
gl_texture* decal = &texture2;

/*

MISC FUNCTIONS

*/

/* forward declaration because uhhhh idk */
void kill();

void checkSDLError(int line = -1)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
		if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
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

/* ======================== */

int MENU_StartGame() {

	mode = loading_mode;
	gamemgr.map_is_initialized = 0;
	return 0;

}

int MENU_AboutPage() {
	ilDeleteImages( 1, &background.imgID ); glDeleteTextures( 1, &background.TextureID );
	//R_IMGLoadTexture(background, "data/bmp/about.png");
	return 0;
}

int MENU_ShowMenuButtons(int pos_x, int pos_y, int width, int height, int gap) {

	ui_button start_game;
	ui_button about_screen;
	ui_button exit_game;

	start_game.pos_x = pos_x;
	start_game.pos_y = pos_y;
	start_game.width = 160;
	start_game.height = 16;
	start_game.title = "new game";
	start_game.textstyle = 0;
	start_game.ptr = (void (*)())&MENU_StartGame;

	UI_Button(start_game);

	about_screen.pos_x = pos_x;
	about_screen.pos_y = (pos_y) + (height * 1) + gap;
	about_screen.width = 160;
	about_screen.height = 16;
	about_screen.title = "about / options";
	about_screen.textstyle = 0;
	about_screen.ptr = (void (*)())&MENU_AboutPage;

	UI_Button(about_screen);

	exit_game.pos_x = pos_x;
	exit_game.pos_y = (pos_y) + (height * 2) + (gap * 2);
	exit_game.width = 160;
	exit_game.height = 16;
	exit_game.title = "exit game";
	exit_game.textstyle = 0;
	exit_game.ptr = (void (*)())&kill;

	UI_Button(exit_game);

	return 0;

}

int main(int argc, char *argv[]) {

	if ( !init() ) {
		printf("KEKTECH FAILED TO START\nCHECK YOUR SDL LIBRARY AND CONTACT THE DISTRIBUTOR OF THE GAME\n");
		return 1;
	}

	if (argc == 2) {
		mode = main_mode;
		/* the limit is 128 - the prefix */
		snprintf(gamemgr.currentmap, 128, "%s/%s", "data/ds", argv[1]);
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

bool initgl() {

	/* JEBANE KURWA GÓWNO */

	//Success flag
	bool success = true;

	R_GLShaderInit();

	//Get vertex attribute location
	gVertexPos3DLocation = glGetAttribLocation( texturequadshader.ID, "VertexPos3D" );
	if( gVertexPos3DLocation == -1 ) {
		printf( "VertexPos3D is not a valid glsl program variable!\n" );
		success = false;
	} else {

		glEnable( GL_TEXTURE_2D );
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Initialize clear color
		glClearColor( 0.f, 0.f, 0.f, 1.f );

		//Initialize DevIL
		ilInit();
		ilClearColour( 255, 255, 255, 000 );

		ILenum ilError = ilGetError();
    		if( ilError != IL_NO_ERROR ) { printf( "Error initializing DevIL! %s\n"); return false; }
	}

	glGenVertexArrays(1, &gVAO);
	//Create VBO
	glGenBuffers( 1, &gVBO );

	//Create IBO
	glGenBuffers( 1, &gIBO );

	return success;
}

bool endgl() {

	glDeleteVertexArrays(1, &gVBO);
/*	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);  */
	return true;

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

	SDL_RenderSetLogicalSize(renderer, GAME_VIEWPORT_WIDTH, GAME_VIEWPORT_HEIGHT);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	R_Clear();
	/* Clear color buffer */
	/* update projection */

	/* ------------------------- */

	// Event loop
	while ( SDL_PollEvent( &e ) != 0 ) {

		// process events
		switch (e.type) {
			case SDL_QUIT:
				A_KillAudioEngine();
				return false;
			case SDL_TEXTINPUT:
				textbox_input += e.text.text;
				continue;
			case SDL_KEYUP:
				if (e.key.keysym.sym == SDLK_BACKSPACE && textbox_input.size()) {
					textbox_input.pop_back();
				} else if (gamemgr.is_paused == false) {
					I_ProcessKeyUpEvent();
				} continue;
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
				} continue;
			case SDL_MOUSEMOTION:
				global_offset = I_GetMouseOffsets(e.motion.x, e.motion.y);

				//printf("MOUSE OFFSETS: x = %d, y = %d\n", e.motion.x, e.motion.y);
				continue;

   			//If a mouse button was pressed
    			case SDL_MOUSEBUTTONDOWN:
        			//If the left mouse button was pressed
        			if( e.button.button == SDL_BUTTON_LEFT ) {
					global_mousemasks_pressed.mouse_left = true;
        			}
				//If the left mouse button was pressed
        			if( e.button.button == SDL_BUTTON_RIGHT ) {
					global_mousemasks_pressed.mouse_right = true;
        			} continue;

   			//If a mouse button was pressed
    			case SDL_MOUSEBUTTONUP:
        			//If the left mouse button was pressed
        			if( e.button.button == SDL_BUTTON_LEFT ) {
					global_mousemasks_released.mouse_left = true;
        			}
				//If the left mouse button was pressed
        			if( e.button.button == SDL_BUTTON_RIGHT ) {
					global_mousemasks_released.mouse_right = true;
        			}
		}
	}

	if (A_IsPlaying(music.source)) {
		A_StreamMUS();
		printf("kurwa\n");
	}

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

//				SDL_RenderCopy(renderer, UI_dashboard.menu_background, NULL, NULL);
				break;

			/* kkui_dashboard (game's main menu) */
			case 255:
				M_ReadMapFile("data/ds/kkui_dashboard/dashboard.ds", texturemgr);
/*				UI_WindowFrameEx(6, 82, 240, 72, 0, 0, 0, 224, 112, 224, "WITAMY W DEMIE ZDS!!!");
				UI_TextLabelEx(8, 98, 224, 112, 224, "AKTUALIZACJA 1.0.2: SNAKE MINIGIERKA DOSTEPNA POD KLAWISZEM V, NOWA WERSJA SILNIKA, AKTUALIZACJE INTERFEJSU POD MASKA, OGOLNE POPRAWKI. DZIEKUJE ZA WSZELKIE WSPARCIE - m4kulatura", 238, true); */
				MENU_ShowMenuButtons(2, 128, 128, 32, 2);
				UI_ShowLog(UI_log.logbuffer);	
				break;
			/* kkui_crash (the so called "NSOD" (nerd screen of death)) */
			case 254:
				UI_CrashScreen(UI_nsod.crash_logbuffer);
				break;
			/* kkui_credit (the credits screen showed at the end of the game) */
			case 253:
				//M_ReadMapFile(gamemgr.currentmap, texturemgr);
				break;
		}
	}

	//R_RenderText(fontshader, "This is sample text", 25.0f, 25.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

	/* 
		PAUSE CHECK
	*/

	if (gamemgr.is_paused == true) {
		UI_FillRectEx(2, GAME_VIEWPORT_HEIGHT / UI_SCALE - 20, GAME_VIEWPORT_WIDTH / UI_SCALE, 20, 255, 255, 255, true);
		UI_TextLabelEx(2,  GAME_VIEWPORT_HEIGHT / UI_SCALE / 2 - 20 / UI_SCALE, 0, 0, 0, "THE GAME IS PAUSED, PRESS F10 TO RESUME IT\nWARNING: MOVING WHILE PAUSED CAN CAUSE ISSUES", GAME_VIEWPORT_WIDTH / UI_SCALE, true);
	}

	//R_RenderTextureQuad({0.0, 0.0, -1.0}, 0.0f, {1.0, 1.0, 1.0}, NULL, R_GetMaterial(texturemgr, "m4kulatura"), NULL, 0.0, texturequadshader);
	/* UPDATE WINDOW AT THE END */
	SDL_GL_SwapWindow( window );
	printf("lmaooo: %d\n", sizeof(projection));
	//SDL_RenderPresent(renderer);
	/*
		WRAP-UP
	*/
//	free(texture1);
	I_ResetMousemasks();
	gamemgr.frame_endtime = SDL_GetTicks64();
	gamemgr.frame_deltatime = gamemgr.frame_endtime - gamemgr.frame_starttime;
	//free(offset);
	/* do nothing if you're in the menu */
	return true;

}

bool init() {

	/* allocate the crash log buffer so windows doesnt complain when shit inevitably fucks itself (:3) */
	UI_nsod.crash_logbuffer = (char*)malloc(1024 * sizeof(char*));
	mode = kkui_dashboard;

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

	if (FT_Init_FreeType(&ft)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	window = SDL_CreateWindow( game_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, game_screen_width, game_screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
	//SDL_ShowCursor(true);
	if ( !window ) {
		std::cout << "Error creating window: " << SDL_GetError()  << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if ( !renderer ) {
		std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	/* load the font data */
	font = TTF_OpenFont("data/res/slkscr.ttf", 8);
	if ( !font ) {
		snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING FONT, FILE DOES NOT EXIST / PERMISSION DENIED"); mode = kkui_crash; return false;
	}

        //Use OpenGL 3.3 core
	if (
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) < 0) {
		snprintf(UI_nsod.crash_logbuffer, 256, "COULD NOT INITIALIZE OPENGL 3.3! YOUR OPERATING SYSTEM / GRAPHICS CARD DOESNT SUPPORT 3D ACCELERATION"); mode = kkui_crash; return false;
	}

	if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32) < 0) {
		if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) < 0) {
			if (SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16) < 0) {
				snprintf(UI_nsod.crash_logbuffer, 256, "COULD NOT INITIALIZE A PROPER Z-BUFFER. YOUR OPERATING SYSTEM / GRAPHICS CARD DOES NOT SUPPORT 16-BIT+ Z-BUFFERS REQUIRED TO RUN THE GAME"); mode = kkui_crash; return false;
			}
		}
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

	/* Create our opengl context and attach it to our window */
	context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE; 
        GLenum glewError = glewInit();
 	checkSDLError(__LINE__);
	/* This makes our buffer swap syncronized with the monitor's vertical refresh */
	SDL_GL_SetSwapInterval(1);

	/* Start OpenAL */
	A_StartAudioEngine();

	// initialize texture manager - tijon
	texturemgr = new game_texture();
	texturemgr->cachedMaterials = std::vector<MaterialDefinition*>();
	sfxmgr = new game_sfx();
	sfxmgr->cachedSounds = std::vector<SoundDefinition*>();
	portraitmgr = new game_avatar(); /* que? */
	portraitmgr->cachedAvatars = std::vector<PortraitDefinition*>();

	/* start sending SDL_TextInput events */
//	SDL_StartTextInput();

	UI_InitLog();
	/* initialize the random number generator */
	RNG_Init();

	initgl();

	/* load textures and sound effects into our memory */
	R_InitTextures(texturemgr);
	A_InitSoundEffects(sfxmgr);
	/* play non-existant dummy music. openal moment */
	A_PlayMUS(A_GetSoundEffect(sfxmgr, "select").c_str());

	printf("\n---------------------------------\n%s\n-------------------------\n", A_GetSoundEffect(sfxmgr, "select").c_str());
	/* initialize the player entity */
//	PLAYER_Init();

	R_LoadFont("data/res/vt323.ttf", 12);

	background_texname = "startbackground";
	strcpy(gamemgr.currentmap, "data/ds/start.ds");

	//SAVE_InitSaveOperation();
	//SAVE_WriteKeyToFile("omg", "haii");
	//SAVE_ReadKeyFromFile();

	ClientInit();

	/* you HAVE to send something, for some reason. will move to UI_InitLog() because of that */
	UI_SendLog(" ");

	return true;
}

void kill() {

	endgl();
	R_FreeMaterial(texturemgr);
	//SDL_StopTextInput();
	free(UI_nsod.crash_logbuffer);

	//mixer.music = NULL;	

	TTF_CloseFont( font );

	SDL_GL_DeleteContext(context);
	SDL_DestroyTexture(textarget);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);


	TTF_Quit(); IMG_Quit(); SDL_Quit();
}
