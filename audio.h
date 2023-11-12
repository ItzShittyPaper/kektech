#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#define OPENMPT_MODULE_RENDER_INTERPOLATIONFILTER_LENGTH 1
#define MAX_BUFFERS 128
#define BUFFER_SIZE 512

#include "libs.h"
#include <vector>

/* 

AUDIO ARCHITECTURE

*/

struct audio_arch {

	/* a single music channel */
//	Mix_Music* music = NULL;

	ALCdevice* device = NULL; // select the "preferred device"
	ALCcontext* context = NULL;

	std::vector<ALuint> buffers;
	ALCuint source;

	SNDFILE* sndfile = NULL;
	SF_INFO sfinfo;
	ALenum format;

	ALint state;

} extern mixer;

struct al_music {

	SNDFILE* sndfile;
	SF_INFO* sfinfo;
	ALenum* err;
	ALenum format;
	ALuint* buffers;
	short* membuf;

} extern music;

extern struct SoundDefinition
{
	std::string soundName;
	std::string pathName;

	//Mix_Chunk* cache;

	
} sounddefinition;

struct game_sfx {
	std::vector<SoundDefinition*> cachedSounds;
} extern *sfxmgr;

void A_LoadSoundEffects(game_sfx* manager, char* path);
void A_FreeSoundEffect(game_sfx* manager);
void A_AddSoundEffect(game_sfx* manager, SoundDefinition* definition);
void A_ClearSoundEffects(game_sfx* manager);
void A_RemoveSoundEffect(game_sfx* manager, SoundDefinition* definition);
//Mix_Chunk* A_GetSoundEffect(game_sfx* manager, const char* sound);
void A_InitSoundEffects(game_sfx* manager);

void A_StartAudioEngine();
void A_KillAudioEngine();
int A_PlaySFX(const char* filename);
int A_MusicUpdateEvent();

#endif // AUDIO_H_INCLUDED 
