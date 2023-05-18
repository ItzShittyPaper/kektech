#include "libs.h"
#define RENDER_SCALE 1

#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED
bool R_Clear();
void ToggleFullscreen(SDL_Window* Window);
void R_InitTextures();
void R_DrawCharacterPortrait(int pos_x, int pos_y, SDL_Texture* texture_index);

void R_DrawPlayer(SDL_Texture* texture_index, int direction);

/* TEXTURE PATH INDEX */
static const char* const values[] {
	"leo/bmp/smiley.png",
	"leo/bmp/leadpipe.png",
	"leo/bmp/branch.png",
	"leo/bmp/bare_hands.png",

	"leo/bmp/characters/leolaus.png"
};

extern struct CharacterPortrait {

	SDL_Rect srcrect;
	SDL_Rect dstrect;

} charportraitbuf;

extern struct CharacterWorldSprite {

	SDL_Rect srcrect;
	SDL_Rect dstrect;

	/* higher = faster */
	int anim_speed = 1;

	enum CharacterDirectionIndex {

		left = 62,
		right = 62,
		up = 95,
		down = 78 

	} directionindex;

	enum CharacterAnimIndex {

		frame1 = 80,
		frame2 = 96,
		idle = 112

	} animindex;

} playerworldsprite;

/* TEXTURE DEFINITIONS */
extern SDL_Texture* glaggle;
extern SDL_Texture* leadpipe;
extern SDL_Texture* branch;
extern SDL_Texture* bare_hands;

extern SDL_Texture* leo_sheet;

// Pointers to our window, renderer, texture, and font
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern TTF_Font* font;


#endif // RENDER_H_INCLUDED 
