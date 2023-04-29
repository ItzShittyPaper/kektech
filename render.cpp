#include "libs.h"
#include "render.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
TTF_Font* font;

SDL_Texture* glaggle;
SDL_Texture* leadpipe;
SDL_Texture* branch;
SDL_Texture* bare_hands;

/* character spritesheet */
SDL_Texture* leo_sheet;

struct CharacterPortrait {

	SDL_Rect srcrect;
	SDL_Rect dstrect;

};

void R_InitTextures() {

	glaggle =    IMG_LoadTexture(renderer, values[0]);
	leadpipe =   IMG_LoadTexture(renderer, values[1]);
	branch =     IMG_LoadTexture(renderer, values[2]);
	bare_hands = IMG_LoadTexture(renderer, values[3]);

	leo_sheet =  IMG_LoadTexture(renderer, values[4]);

}

bool R_Clear() {

	// Clear the window to white
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );		
	return true;

};

void R_DrawCharacterPortrait(int pos_x, int pos_y, SDL_Texture* texture_index) {

	CharacterPortrait portrait;

	portrait.srcrect.x = 0;
	portrait.srcrect.y = 64;
	portrait.srcrect.w = 64;
	portrait.srcrect.h = 64;
	
	portrait.dstrect.x = pos_x;
	portrait.dstrect.y = pos_y;
	portrait.dstrect.w = 64;
	portrait.dstrect.h = 64;

	SDL_RenderCopy(renderer, texture_index, &portrait.srcrect, &portrait.dstrect); 

}

void ToggleFullscreen(SDL_Window* Window) {

	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);

};
