#include "libs.h"

#define RENDER_SCALE 1

#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED
bool R_Clear();
void ToggleFullscreen(SDL_Window* Window);
void R_InitTextures();

/* TEXTURE PATH INDEX */
static const char* const values[] {
	"leo/bmp/smiley.png",
	"leo/bmp/leadpipe.png",
	"leo/bmp/branch.png",
	"leo/bmp/bare_hands.png"
};

/* TEXTURE DEFINITIONS */
extern SDL_Texture* glaggle;
extern SDL_Texture* leadpipe;
extern SDL_Texture* branch;
extern SDL_Texture* bare_hands;

// Pointers to our window, renderer, texture, and font
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern TTF_Font* font;


#endif // RENDER_H_INCLUDED 
