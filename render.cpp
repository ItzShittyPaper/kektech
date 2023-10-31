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
	R_LoadMaterials(manager, "data/mat/game.mat");
}

bool R_Clear() {

	// Clear the window to black
	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );		
	return true;

};

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


void ToggleFullscreen(SDL_Window* Window) {

	Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
	bool IsFullscreen = SDL_GetWindowFlags(Window) & FullscreenFlag;
	SDL_SetWindowFullscreen(Window, IsFullscreen ? 0 : FullscreenFlag);
	SDL_ShowCursor(IsFullscreen);

};
