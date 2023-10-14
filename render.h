#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED

#include "libs.h"
#include <vector>

#define RENDER_SCALE 1
#define TARGET_FPS 60

extern int animplayer_character;

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

/* TEXTURE DEFINITIONS */

// Pointers to our window, renderer, texture, and font
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern TTF_Font* font;
extern game_texture* texturemgr;

void ToggleFullscreen(SDL_Window* Window);
void R_DrawBackground();
void R_FadeOutBackground();

void R_InitTextures(game_texture* manager);
void R_FreeMaterial(game_texture* manager);
void R_AddMaterial(game_texture* manager, MaterialDefinition* definition);
void R_ClearMaterials(game_texture* manager);
void R_RemoveMaterial(game_texture* manager, MaterialDefinition* definition);
void R_LoadMaterials(game_texture* manager, char* path);
SDL_Texture* R_GetMaterial(game_texture* manager, const char* material);

bool R_Clear();

#endif // RENDER_H_INCLUDED 
