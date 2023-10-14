#ifndef CLIENT_RENDER_H_INCLUDED
#define CLIENT_RENDER_H_INCLUDED

#include "engine.h"

/* structures used by the game, some aren't used technically but who cares i'll fix it later */
struct CharacterPortrait {

	int animplayer = 0;

	SDL_Rect srcrect;
	SDL_Rect dstrect;

};

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

/* drawing functions */
void R_DrawPlayer(SDL_Texture* texture_index, int direction);
void R_DrawCharacterPortrait(SDL_Texture* texture_index);
void R_ResetPortraitAnim();
void NPC_DrawEntity(SDL_Texture* texture_index, int pos_x, int pos_y, int direction, char* dialog_path, int type);

//extern SDL_Texture* R_GetMaterial(game_texture* manager, const char* material);

#endif // CLIENT_RENDER_H_INCLUDED 
