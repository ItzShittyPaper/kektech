#include "engine.h"
#include "client_render.h"

/* active dialog character portrait buffer */
//CharacterPortrait charportraitbuf;
/* initializing player sprite struct */
CharacterWorldSprite playerworldsprite;
CharacterPortrait portrait;
int animplayer_character = 0;

void R_ResetPortraitAnim() {

		portrait.animplayer = 0;
}

void R_DrawCharacterPortrait(gl_texture texture_index, int expression) {

	/* CHARACTER EXPRESSION INDEX

		0 - IDLE
		1 - ANGRY
		2 - BLUSHY / EMBARASSED
		3 - FIGHT
		4 - HALF-NAKED

	*/

	portrait.clip->width = 0.312f;
	portrait.clip->height = 0.312f;
	
	switch(expression) {

		case 0:
			portrait.clip->pos_x = 0;
			portrait.clip->pos_y = 0;
			break;
		case 1:
			portrait.clip->pos_x = (portrait.clip->width * 1);
			portrait.clip->pos_y = 0;
			break;
		case 2:
			portrait.clip->pos_x = (portrait.clip->width * 2);
			portrait.clip->pos_y = 0;
			break;
		case 3:
			portrait.clip->pos_x = 0;
			portrait.clip->pos_y = (portrait.clip->height * 1);
			break;
		case 4:
			portrait.clip->pos_x = (portrait.clip->width * 1);
			portrait.clip->pos_y = (portrait.clip->height * 1);
			break;
	}

	portrait.dstrect.w = 214;
	portrait.dstrect.h = 360;

	portrait.dstrect.x = 72 + (portrait.dstrect.w * (dialog.character_count - 2));
	portrait.dstrect.y = GAME_VIEWPORT_HEIGHT - portrait.dstrect.h;

	if (portrait.animplayer < 254) {
		//SDL_SetTextureAlphaMod(texture_index, portrait.animplayer);
		portrait.animplayer += 8;
	}
	if (portrait.animplayer > 254) {
		portrait.animplayer = 255;
		//SDL_SetTextureAlphaMod(texture_index, 255);
	}

	R_setQuadSpritesheetCoords(portrait.clip->pos_x, portrait.clip->pos_y, portrait.clip->width, portrait.clip->height, texture_index);
	R_RenderTextureQuad(glm::vec3(0.0f, -0.2f, -0.0f), glm::radians(0.0f), glm::vec3(1.5f, 1.5f, 1.0f), portrait.clip, texture_index, NULL, 0.0, texturequadshader);

}

void R_DrawPlayer(gl_texture texture_index, int direction) {

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
//	if (direction != 1) { SDL_RenderCopy(renderer, texture_index, &playerworldsprite.srcrect, &playerworldsprite.dstrect); }
//	else { SDL_RenderCopyEx(renderer, texture_index, &playerworldsprite.srcrect, &playerworldsprite.dstrect, 0, NULL, SDL_FLIP_HORIZONTAL); }

	/* animation controller check */
	if (player.is_moving == 1) {
		animplayer5 = animplayer5 + 1 * playerworldsprite.anim_speed;
	}

}

void NPC_DrawEntity(gl_texture texture_index, int pos_x, int pos_y, int direction, char* dialog_path, int type) {

	helper_ent npc;

	//UI_FillRect(player.pos_x, player.pos_y, 16, 16, false);
	npc.srcrect.w = 16;
	npc.srcrect.h = 16;

	npc.dialog = dialog_path;

	switch (direction) {

		case 0:
			npc.srcrect.x = 0;
			npc.srcrect.y = 0;
			break;

		case 1:	
			npc.srcrect.x = 0;
			npc.srcrect.y = 0;
			break;

		case 2:	
			npc.srcrect.x = 0;
			npc.srcrect.y = 16;
			break;

		case 3:	
			npc.srcrect.x = 0;
			npc.srcrect.y = 32;
			break;

		default:
			npc.srcrect.x = 0;
			npc.srcrect.y = 0;
			break;

	

	}

	/* setting destination coordinates */
	npc.dstrect.x = pos_x * 16;
	npc.dstrect.y = pos_y * 16;
	npc.dstrect.w = 16;
	npc.dstrect.h = 16;

	npc.intrect.x = (pos_x * 16) - 2;
	npc.intrect.y = (pos_y * 16) - 2;
	npc.intrect.w = 20;
	npc.intrect.h = 20;

	/* perform collision checks */
	M_PlayerTileCollide(npc.dstrect, player.collider);
	NPC_HelperActivate(player.collider, npc.intrect, npc.dialog);

	/* direction check flipping the sprite horizontally if needed */
//	if (direction != 1) { SDL_RenderCopy(renderer, texture_index, &npc.srcrect, &npc.dstrect);  }
//	else { SDL_RenderCopyEx(renderer, texture_index, &npc.srcrect, &npc.dstrect, 0, NULL, SDL_FLIP_HORIZONTAL); }

}

