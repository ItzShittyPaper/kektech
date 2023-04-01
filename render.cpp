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

void R_InitTextures() {

	glaggle =    IMG_LoadTexture(renderer, values[0]);
	leadpipe =   IMG_LoadTexture(renderer, values[1]);
	branch =     IMG_LoadTexture(renderer, values[2]);
	bare_hands = IMG_LoadTexture(renderer, values[3]);

}

bool R_Clear() {

	// Clear the window to white
	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
	SDL_RenderClear( renderer );		
	return true;

};

void ToggleFullscreen(SDL_Window* Window) {

	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);

};
