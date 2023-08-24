#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "libs.h"
#include <vector>

/* 

AUDIO ARCHITECTURE

*/

struct audio_arch {

	/* a single music channel */
	Mix_Music* music = NULL;

} extern mixer;

extern struct SoundDefinition
{
	std::string soundName;
	std::string pathName;

	Mix_Chunk* cache;

	
} sounddefinition;

struct game_sfx {
	std::vector<SoundDefinition*> cachedSounds;
} extern *sfxmgr;

void A_LoadSoundEffects(game_sfx* manager, char* path);
void A_FreeSoundEffect(game_sfx* manager);
void A_AddSoundEffect(game_sfx* manager, SoundDefinition* definition);
void A_ClearSoundEffects(game_sfx* manager);
void A_RemoveSoundEffect(game_sfx* manager, SoundDefinition* definition);
Mix_Chunk* A_GetSoundEffect(game_sfx* manager, const char* sound);
void A_InitSoundEffects(game_sfx* manager);

int A_MusicUpdateEvent();

#endif // AUDIO_H_INCLUDED 
