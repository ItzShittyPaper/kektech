#include "libs.h"
#include "audio.h"

#include "ui.h"
#include "main.h"

audio_arch mixer;
game_sfx* sfxmgr;

int A_MusicUpdateEvent() {

	//If there is no music playing
	if( Mix_PlayingMusic() == 0 ) {
		//Play the music
		Mix_PlayMusic( mixer.music, -1 );
	}
	return 0;
}

void A_FreeSoundEffect(game_sfx* manager)
{
	A_ClearSoundEffects(manager);
	delete manager;
}

void A_LoadSoundEffects(game_sfx* manager, const char* path) {

	FILE* file = fopen(path, "r");
	if (file == NULL) { snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING SOUND EFFECT DEFINITIONS, FILE DOES NOT EXIST / PERMISSION DENIED\nSFX PATH: %s\n"); mode = kkui_crash; return; }

	char soundChunk[128];
	/* parse line by line */
	while (fgets(soundChunk, sizeof(soundChunk), file) != NULL) {

		SoundDefinition* def = new SoundDefinition();
		def->soundName = std::string();
		def->pathName = std::string();

		// this should be sound id name.
		char* tok = strtok(soundChunk, ";");
		def->soundName = tok;
		printf("%s, ", tok);

		// this should be the sfx name
		tok = strtok(NULL, ";");	
		def->pathName = tok;
		printf("%s, ", tok);

		A_AddSoundEffect(manager, def);
	}
}

void A_AddSoundEffect(game_sfx* manager, SoundDefinition* definition)
{
	definition->cache = Mix_LoadWAV(definition->pathName.c_str());
	printf(definition->soundName.c_str());
	printf(definition->pathName.c_str());
	manager->cachedSounds.push_back(definition);

	if (!definition->cache)
	{
		printf(Mix_GetError());
	}
}

void A_ClearSoundEffects(game_sfx* manager)
{
	for (int i = 0; i < manager->cachedSounds.size(); i++)
	{
		SoundDefinition* def = manager->cachedSounds[i];	
		if (def->cache)
		{
			Mix_FreeChunk(def->cache);
		}
	}

	manager->cachedSounds.clear();
}

void A_RemoveSoundEffect(game_sfx* manager, SoundDefinition* definition)
{
	for (int i = 0; i < manager->cachedSounds.size(); i++)
	{
		SoundDefinition* def = manager->cachedSounds[i];
		if (def == definition)
		{
			Mix_FreeChunk(def->cache);
			manager->cachedSounds.erase(manager->cachedSounds.begin() + i);
			return;
		}
	}
}

Mix_Chunk* A_GetSoundEffect(game_sfx* manager, const char* sound)
{
	for (int i = 0; i < manager->cachedSounds.size(); i++)
	{
		SoundDefinition* definition = manager->cachedSounds[i];
		if (strcmp(definition->soundName.c_str(), sound) == 0)
		{
			return definition->cache;
		}
	}
	return nullptr;
}
	
void A_InitSoundEffects(game_sfx* manager) {
	A_LoadSoundEffects(manager, "leo/mat/game.sfx");
}

