#include "libs.h"
#include "audio.h"

#include "ui.h"
#include "main.h"

audio_arch mixer;
al_music music;
game_sfx* sfxmgr;
/*
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
	* parse line by line *
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
	A_LoadSoundEffects(manager, "data/mat/game.sfx");
}
*/
void A_StartAudioEngine() {

	mixer.device = alcOpenDevice(NULL); // select the "preferred device"
	mixer.context = alcCreateContext(mixer.device,NULL);

	if (mixer.device) {
		mixer.context = alcCreateContext(mixer.device,NULL);
		alcMakeContextCurrent(mixer.context);
	} else { return; }

	/* check for EAX 2.0 support */
	alIsExtensionPresent("EAX2.0");


}

void A_KillAudioEngine() {

/*	alDeleteBuffers(MAX_OAL_BUFS, &mixer.buffer);	

	mixer.context = alcGetCurrentContext();
	mixer.device = alcGetContextsDevice(mixer.context);

    	alDeleteSources(1, &mixer.source);
    	alDeleteBuffers(1, &mixer.buffer);
*/
	alcMakeContextCurrent(NULL);
	alcDestroyContext(mixer.context);
	alcCloseDevice(mixer.device);

}

/* LoadBuffer loads the named audio file into an OpenAL buffer object, and
 * returns the new buffer ID.
 */
static ALuint A_LoadSFX(const char *filename)
{
	ALenum err, format;
	ALuint buffer;
	SNDFILE* sndfile;
	SF_INFO sfinfo;
	short* membuf;
	sf_count_t num_frames;
	ALsizei num_bytes;

	/* Open the audio file and check that it's usable. */
	sndfile = sf_open(filename, SFM_READ, &sfinfo);
	if (!sndfile)
	{
		fprintf(stderr, "Could not open audio in %s: %s\n", filename, sf_strerror(sndfile));
		return 0;
	}
	if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
	{
		fprintf(stderr, "Bad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
		sf_close(sndfile);
		return 0;
	}

	/* Get the sound format, and figure out the OpenAL format */
	format = AL_NONE;
	if (sfinfo.channels == 1)
		format = AL_FORMAT_MONO16;
	else if (sfinfo.channels == 2)
		format = AL_FORMAT_STEREO16;
	else if (sfinfo.channels == 3)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (sfinfo.channels == 4)
	{
		if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			format = AL_FORMAT_BFORMAT3D_16;
	}
	if (!format)
	{
		fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
		sf_close(sndfile);
		return 0;
	}

	/* Decode the whole audio file to a buffer. */
	membuf = static_cast<short*>(malloc((size_t)(sfinfo.frames * sfinfo.channels) * sizeof(short)));

	num_frames = sf_readf_short(sndfile, membuf, sfinfo.frames);
	if (num_frames < 1)
	{
		free(membuf);
		sf_close(sndfile);
		fprintf(stderr, "Failed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
		return 0;
	}
	num_bytes = (ALsizei)(num_frames * sfinfo.channels) * (ALsizei)sizeof(short);

	/* Buffer the audio data into a new buffer object, then free the data and
	 * close the file.
	 */
	buffer = 0;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, format, membuf, num_bytes, sfinfo.samplerate);

	free(membuf);
	sf_close(sndfile);

	/* Check if an error occured, and clean up if so. */
	err = alGetError();
	if (err != AL_NO_ERROR)
	{
		fprintf(stderr, "OpenAL Error: %s\n", alGetString(err));
		if (buffer && alIsBuffer(buffer))
			alDeleteBuffers(1, &buffer);
		return 0;
	}

	mixer.buffers.push_back(buffer);  // add to the list of known buffers

	return buffer;
}

int A_LoadMUS(const char* filename) {

	alGenBuffers(MAX_BUFFERS, music.buffers);
	std::size_t frame_size;

	music.sndfile = sf_open(filename, SFM_READ, music.sfinfo);
	if (!music.sndfile)
	{
		throw("could not open provided music file -- check path");
	}

	/* Get the sound format, and figure out the OpenAL format */
	if (music.sfinfo->channels == 1)
		music.format = AL_FORMAT_MONO16;
	else if (music.sfinfo->channels == 2)
		music.format = AL_FORMAT_STEREO16;
	else if (music.sfinfo->channels == 3)
	{
		if (sf_command(music.sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			music.format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (music.sfinfo->channels == 4)
	{
		if (sf_command(music.sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			music.format = AL_FORMAT_BFORMAT3D_16;
	}
	if (!music.format)
	{
		sf_close(music.sndfile);
		music.sndfile = NULL;
		throw("Unsupported channel count from file");
	}

	frame_size = ((size_t)BUFFER_SIZE * (size_t)music.sfinfo->channels) * sizeof(short);
	music.membuf = static_cast<short*>(malloc(frame_size));

}

void A_UpdateMUS() {

	ALint processed, state;

	// clear error 
	//alGetError();
	/* Get relevant source info */
	alGetSourcei(mixer.source, AL_SOURCE_STATE, &state);
	alGetSourcei(mixer.source, AL_BUFFERS_PROCESSED, &processed);
	AL_CheckAndThrow();

	/* Unqueue and handle each processed buffer */
	while (processed > 0)
	{
		ALuint bufid;
		sf_count_t slen;

		alSourceUnqueueBuffers(mixer.source, 1, &bufid);
		processed--;

		/* Read the next chunk of data, refill the buffer, and queue it
		 * back on the source */
		slen = sf_readf_short(mixer.sndfile, mixer.membuf, BUFFER_SAMPLES);
		if (slen > 0)
		{
			slen *= music.sfinfo->channels * (sf_count_t)sizeof(short);
			alBufferData(bufid, music.format, music.membuf, (ALsizei)slen,
				music.sfinfo->samplerate);
			alSourceQueueBuffers(mixer.source, 1, &bufid);
		}
		if (alGetError() != AL_NO_ERROR)
		{
			throw("error buffering music data");
		}
	}

	/* Make sure the source hasn't underrun */
	if (state != AL_PLAYING && state != AL_PAUSED)
	{
		ALint queued;

		/* If no buffers are queued, playback is finished */
		alGetSourcei(p_Source, AL_BUFFERS_QUEUED, &queued);
		AL_CheckAndThrow();
		if (queued == 0)
			return;

		alSourcePlay(p_Source);
		AL_CheckAndThrow();
	}

}

int A_PlaySFX(const char* filename) {

	A_StartAudioEngine();
	ALint buffer;
	ALfloat offset;
	buffer = A_LoadSFX(filename);

	alGenSources(1, &mixer.source);
	alSourcei(mixer.source, AL_BUFFER, (ALint)buffer);

	/* Play the sound until it finishes. */
	alSourcePlay(mixer.source);

	assert(alGetError()==AL_NO_ERROR && "Failed to setup sound source");

	while (mixer.state == AL_PLAYING) {
        	alGetSourcei(mixer.source, AL_SOURCE_STATE, &mixer.state);
        	// check for errors
	}	

	return 0;

}
