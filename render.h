#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "libs.h"
#include <vector>

#define RENDER_SCALE 1
#define TARGET_FPS 60

extern int animplayer_character;

bool R_Clear();
void ToggleFullscreen(SDL_Window* Window);
void R_ResetPortraitAnim();
void R_DrawBackground();
void R_FadeOutBackground();
void R_DrawCharacterPortrait(SDL_Texture* texture_index);

/* drawing functions */
void R_DrawPlayer(SDL_Texture* texture_index, int direction);
void NPC_DrawEntity(SDL_Texture* texture_index, int pos_x, int pos_y, int direction, char* dialog_path, int type);

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

// additional stuff add here and modify parser.
extern struct MaterialDefinition
{
	std::string materialName;
	std::string textureName;

	SDL_Texture* cache;

	
} materialdefinition;

struct kVector;

struct game_texture {
	std::vector<MaterialDefinition*> cachedMaterials;
} extern *texturemgr;

void R_InitTextures(game_texture* manager);

void R_FreeMaterial(game_texture* manager);
void R_AddMaterial(game_texture* manager, MaterialDefinition* definition);
void R_ClearMaterials(game_texture* manager);
void R_RemoveMaterial(game_texture* manager, MaterialDefinition* definition);
void R_LoadMaterials(game_texture* manager, char* path);
SDL_Texture* R_GetMaterial(game_texture* manager, const char* material);

/* TEXTURE DEFINITIONS */

// Pointers to our window, renderer, texture, and font
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern TTF_Font* font;


#endif // RENDER_H_INCLUDED 
