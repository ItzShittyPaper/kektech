
#define RENDER_SCALE 1

#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "libs.h"
#include <vector>

bool R_Clear();
void ToggleFullscreen(SDL_Window* Window);
void R_DrawCharacterPortrait(int pos_x, int pos_y, SDL_Texture* texture_index);

/* drawing functions */
void R_DrawPlayer(SDL_Texture* texture_index, int direction);
void NPC_DrawEntity(SDL_Texture* texture_index, int pos_x, int pos_y, int direction, char* dialog_path, int type);

/* TEXTURE PATH INDEX */
static const char* const values[] {
	"leo/bmp/smiley.png",
	"leo/bmp/leadpipe.png",
	"leo/bmp/branch.png",
	"leo/bmp/bare_hands.png",

	"leo/bmp/characters/leolaus.png",
	"leo/bmp/characters/zlewhead.png"
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
} extern Texture;

void R_InitTextures(game_texture* manager);

void R_FreeMaterial(game_texture* manager);
void R_AddMaterial(game_texture* manager, MaterialDefinition* definition);
void R_ClearMaterials(game_texture* manager);
void R_RemoveMaterial(game_texture* manager, MaterialDefinition* definition);
void R_LoadMaterials(game_texture* manager, char* path);
SDL_Texture* R_GetMaterial(game_texture* manager, const char* material);

/* TEXTURE DEFINITIONS */
extern SDL_Texture* glaggle;
extern SDL_Texture* leadpipe;
extern SDL_Texture* branch;
extern SDL_Texture* bare_hands;

extern SDL_Texture* leo_sheet;
extern SDL_Texture* zlew_sheet;

// Pointers to our window, renderer, texture, and font
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern TTF_Font* font;


#endif // RENDER_H_INCLUDED 
