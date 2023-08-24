#include "libs.h"
#include "render.h"
#include "map.h"
#include "ui.h"
#include "main.h"
#include "vector.h"

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
TTF_Font* font;

game_texture* texturemgr;

/* active dialog character portrait buffer */
//CharacterPortrait charportraitbuf;
/* initializing player sprite struct */
CharacterWorldSprite playerworldsprite;

CharacterPortrait portrait;

int animplayer_character = 0;

void R_FreeMaterial(game_texture* manager)
{
	R_ClearMaterials(manager);
	delete manager;
}

void R_AddMaterial(game_texture* manager, MaterialDefinition* definition)
{
	definition->cache = IMG_LoadTexture(renderer, definition->textureName.c_str());
	printf(definition->materialName.c_str());
	printf(definition->textureName.c_str());
	manager->cachedMaterials.push_back(definition);

	if (!definition->cache)
	{
		printf(IMG_GetError());
	}
}

void R_ClearMaterials(game_texture* manager)
{
	for (int i = 0; i < manager->cachedMaterials.size(); i++)
	{
		MaterialDefinition* def = manager->cachedMaterials[i];	
		if (def->cache)
		{
			SDL_DestroyTexture(def->cache);
		}
	}

	manager->cachedMaterials.clear();
}

void R_RemoveMaterial(game_texture* manager, MaterialDefinition* definition)
{
	for (int i = 0; i < manager->cachedMaterials.size(); i++)
	{
		MaterialDefinition* def = manager->cachedMaterials[i];
		if (def == definition)
		{
			SDL_DestroyTexture(def->cache);
			manager->cachedMaterials.erase(manager->cachedMaterials.begin() + i);
			return;
		}
	}
}

void R_LoadMaterials(game_texture* manager, char* path)
{
	FILE* file = fopen(path, "r");
	if (file == NULL) { snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING MATERIAL DEFINITIONS, FILE DOES NOT EXIST / PERMISSION DENIED\nMAT PATH: %s\n"); mode = kkui_crash; return; }

	char matChunk[LINE_BUF];
	/* parse line by line */
	while (fgets(matChunk, sizeof(matChunk), file) != NULL) {

		MaterialDefinition* def = new MaterialDefinition();
		def->materialName = std::string();
		def->textureName = std::string();

		// this should be material name.
		char* tok = strtok(matChunk, ";");
		def->materialName = tok;
		printf("%s, ", tok);

		// this should be texture name
		tok = strtok(NULL, ";");	
		def->textureName = tok;
		printf("%s, ", tok);

		R_AddMaterial(manager, def);
	}

}

SDL_Texture* R_GetMaterial(game_texture* manager, const char* material)
{
	for (int i = 0; i < manager->cachedMaterials.size(); i++)
	{
		MaterialDefinition* definition = manager->cachedMaterials[i];
		if (strcmp(definition->materialName.c_str(), material) == 0)
		{
			return definition->cache;
		}
	}
	return nullptr;
}
	
void R_InitTextures(game_texture* manager) {
	R_LoadMaterials(manager, "leo/mat/game.mat");
}

bool R_Clear() {

	// Clear the window to black
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );		
	return true;

};

void R_ResetPortraitAnim() {

	portrait.animplayer = 0;

}

void R_DrawBackground() {

	if (UI_dashboard.animplayer < 255) {
		/* render the map background */
		SDL_SetTextureAlphaMod(UI_dashboard.menu_background, UI_dashboard.animplayer);
		UI_dashboard.animplayer += 8;
		if (UI_dashboard.animplayer >= 255) { UI_dashboard.animplayer = 255; }
	}
	SDL_RenderCopy(renderer, UI_dashboard.menu_background, NULL, NULL);

}

void R_FadeOutBackground() {

	if (UI_dashboard.animplayer > 0) {
		/* render the map background */
		SDL_SetTextureAlphaMod(UI_dashboard.menu_background, UI_dashboard.animplayer);
		UI_dashboard.animplayer -= 8;
	}
	SDL_RenderCopy(renderer, UI_dashboard.menu_background, NULL, NULL);

}

void R_DrawCharacterPortrait(SDL_Texture* texture_index) {

	portrait.srcrect.x = 0;
	portrait.srcrect.y = 0;
	portrait.srcrect.w = 214;
	portrait.srcrect.h = 464;
	
	portrait.dstrect.x = 214 * dialog.character_count;
	portrait.dstrect.y = game_viewport_height - 464 - 72;
	portrait.dstrect.w = 214;
	portrait.dstrect.h = 464;

	if (portrait.animplayer < 255) {
		SDL_SetTextureAlphaMod(texture_index, portrait.animplayer);
		portrait.animplayer += 16;
	}

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

void NPC_DrawEntity(SDL_Texture* texture_index, int pos_x, int pos_y, int direction, char* dialog_path, int type) {

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
	if (direction != 1) { SDL_RenderCopy(renderer, texture_index, &npc.srcrect, &npc.dstrect);  }
	else { SDL_RenderCopyEx(renderer, texture_index, &npc.srcrect, &npc.dstrect, 0, NULL, SDL_FLIP_HORIZONTAL); }

}

void ToggleFullscreen(SDL_Window* Window) {

	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);

};
