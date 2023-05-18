#include "libs.h"
#include "render.h"
#include "ui.h"
#include "main.h"

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
/* active dialog character portrait buffer */
//CharacterPortrait charportraitbuf;
/* initializing player sprite struct */
CharacterWorldSprite playerworldsprite;

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

void R_DrawPlayer(SDL_Texture* texture_index, int direction) {

	//UI_FillRect(player.pos_x, player.pos_y, 16, 16, false);
	playerworldsprite.srcrect.w = 16;
	playerworldsprite.srcrect.h = 16;

	switch (direction) {

		case 0:
			playerworldsprite.srcrect.x = 112;
			playerworldsprite.srcrect.y = playerworldsprite.left;
			break;

		case 1:	
			playerworldsprite.srcrect.x = 112;
			playerworldsprite.srcrect.y = playerworldsprite.right;
			break;

		case 2:	
			playerworldsprite.srcrect.x = 112;
			playerworldsprite.srcrect.y = playerworldsprite.up;
			break;

		case 3:	
			playerworldsprite.srcrect.x = 112;
			playerworldsprite.srcrect.y = playerworldsprite.down;
			break;
	
	}

	/* weird animation code, it's not the perfect solution but animation code is hard and i don't want to do it */
	if (animplayer5 >= 1) { playerworldsprite.srcrect.x = playerworldsprite.frame1; }
	if (animplayer5 >= 16) { playerworldsprite.srcrect.x = playerworldsprite.idle; }
	if (animplayer5 >= 32) { playerworldsprite.srcrect.x = playerworldsprite.frame2; }
	if (animplayer5 >= 48) { playerworldsprite.srcrect.x = playerworldsprite.idle; }
	if (animplayer5 >= 64) { animplayer5 = 0; }

	/* setting destination coordinates */
	playerworldsprite.dstrect.x = player.pos_x;
	playerworldsprite.dstrect.y = player.pos_y;
	playerworldsprite.dstrect.w = 16;
	playerworldsprite.dstrect.h = 16;

	/* direction check flipping the sprite horizontally if needed */
	if (direction != 1) { SDL_RenderCopy(renderer, texture_index, &playerworldsprite.srcrect, &playerworldsprite.dstrect); }
	else { SDL_RenderCopyEx(renderer, texture_index, &playerworldsprite.srcrect, &playerworldsprite.dstrect, 0, NULL, SDL_FLIP_HORIZONTAL); }

	/* animation controller check */
	if (player.is_moving == 1) {
		animplayer5 = animplayer5 + 1 * playerworldsprite.anim_speed;
	}

}

void ToggleFullscreen(SDL_Window* Window) {

	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);

};
