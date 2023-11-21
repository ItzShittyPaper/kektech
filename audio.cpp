#include "libs.h"
#include "audio.h"

#include "ui.h"
#include "main.h"

#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>

audio_arch mixer;
al_music music;
game_sfx* sfxmgr;

void A_FreeSoundEffect(game_sfx* manager)
{
	A_ClearSoundEffects(manager);
	delete manager;
}

void A_LoadSoundEffects(game_sfx* manager, const char* path) {

	FILE* file = fopen(path, "r");
	if (file == NULL) { snprintf(UI_nsod.crash_logbuffer, 256, "ERROR LOADING SOUND EFFECT DEFINITIONS, FILE DOES NOT EXIST / PERMISSION DENIED\nSFX PATH: %s\n", path); mode = kkui_crash; return; }

	char soundChunk[128];
	/* parse line by line */
	while (fgets(soundChunk, sizeof(soundChunk), file) != NULL) {

		SoundDefinition* def = new SoundDefinition();
		def->soundName = std::string();
		def->pathName = std::string();

		// this should be sound id name.

		/* WHO CARES ABOUT PRINTING ANYWAYS ;3 */

		char* tok = strtok(soundChunk, ";");
		def->soundName = tok;
		//printf("%s, ", tok);

		// this should be the sfx name
		tok = strtok(NULL, ";");	
		def->pathName = tok;

		//printf("%s, ", tok);

		A_AddSoundEffect(manager, def);
	}
}

void A_AddSoundEffect(game_sfx* manager, SoundDefinition* definition)
{
	printf(definition->soundName.c_str());
	printf(definition->pathName.c_str());
	manager->cachedSounds.push_back(definition);
}

void A_ClearSoundEffects(game_sfx* manager)
{
	for (int i = 0; i < manager->cachedSounds.size(); i++)
	{
		SoundDefinition* def = manager->cachedSounds[i];	
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
			manager->cachedSounds.erase(manager->cachedSounds.begin() + i);
			return;
		}
	}
}

std::string A_GetSoundEffect(game_sfx* manager, const char* sound)
{
	for (int i = 0; i < manager->cachedSounds.size(); i++)
	{
		SoundDefinition* definition = manager->cachedSounds[i];
		if (strcmp(definition->soundName.c_str(), sound) == 0)
		{
			return definition->pathName;
		}
	}
	return 0;
}
	
void A_InitSoundEffects(game_sfx* manager) {
	A_LoadSoundEffects(manager, "data/mat/game.sfx");
}

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

bool A_IsPlaying(ALuint source) {

	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);
	return (state == AL_PLAYING);

}

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
		fprintf(stderr, "\nCould not open audio in %s: %s\n", filename, sf_strerror(sndfile));
		return 0;
	}
	if (sfinfo.frames < 1 || sfinfo.frames >(sf_count_t)(INT_MAX / sizeof(short)) / sfinfo.channels)
	{
		fprintf(stderr, "\nBad sample count in %s (%" PRId64 ")\n", filename, sfinfo.frames);
		sf_close(sndfile);
		return 0;
	}

	/* Get the sound format, and figure out the OpenAL format */
	switch(sfinfo.channels) {
		case 1:
			format = AL_FORMAT_MONO16;
			break;
		case 2:
			format = AL_FORMAT_STEREO16;
			break;
		case 3:
			if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format = AL_FORMAT_BFORMAT2D_16;
			break;
		case 4:
			if (sf_command(sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				format = AL_FORMAT_BFORMAT3D_16;
			break;
		default:
			fprintf(stderr, "\nUnsupported channel count: %d\n", sfinfo.channels);
			sf_close(sndfile);
			return 0;
	}
	if (!format)
	{
		fprintf(stderr, "\nUnsupported channel count: %d\n", sfinfo.channels);
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
		fprintf(stderr, "\nFailed to read samples in %s (%" PRId64 ")\n", filename, num_frames);
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

void A_LoadMUS(const char* filename) {

	alGenSources(1, &music.source);
	alGenBuffers(MAX_BUFFERS, music.buffers);
	std::size_t frame_size;

	printf(filename);
	music.sndfile = sf_open(filename, SFM_READ, &music.sfinfo);
	if (!music.sndfile)
	{
		printf("could not open provided music file -- check path\n");
	}

	switch(music.sfinfo.channels) {
		case 1:
			music.format = AL_FORMAT_MONO16;
			break;
		case 2:
			music.format = AL_FORMAT_STEREO16;
			break;
		case 3:
			if (sf_command(music.sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				music.format = AL_FORMAT_BFORMAT2D_16;
			break;
		case 4:
			if (sf_command(music.sndfile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
				music.format = AL_FORMAT_BFORMAT3D_16;
			break;
		default:
			sf_close(music.sndfile);
			music.sndfile = NULL;
			printf("Unsupported channel count from file\n");
	}

	frame_size = ((size_t)BUFFER_SIZE * (size_t)music.sfinfo.channels) * sizeof(short);
	music.membuf = static_cast<short*>(malloc(frame_size));

}

void A_UpdateMUS() {

	ALint processed, state;

	// clear error 
	alGetError();
	/* Get relevant source info */
	alGetSourcei(music.source, AL_SOURCE_STATE, &state);
	alGetSourcei(music.source, AL_BUFFERS_PROCESSED, &processed);
	//AL_CheckAndThrow();

	/* Unqueue and handle each processed buffer */
	while (processed > 0)
	{
		ALuint bufid;
		sf_count_t slen;

		alSourceUnqueueBuffers(music.source, 1, &bufid);
		processed--;

		/* Read the next chunk of data, refill the buffer, and queue it
		 * back on the source */
		slen = sf_readf_short(music.sndfile, music.membuf, BUFFER_SIZE);
		if (slen > 0)
		{
			slen *= music.sfinfo.channels * (sf_count_t)sizeof(short);
			alBufferData(bufid, music.format, music.membuf, (ALsizei)slen,
				music.sfinfo.samplerate);
			alSourceQueueBuffers(music.source, 1, &bufid);
		}
		if (alGetError() != AL_NO_ERROR)
		{
			printf("error buffering music data\n");
		}
	}

	/* Make sure the source hasn't underrun */
	if (state != AL_PLAYING && state != AL_PAUSED)
	{
		ALint queued;

		/* If no buffers are queued, playback is finished */
		alGetSourcei(music.source, AL_BUFFERS_QUEUED, &queued);
		//AL_CheckAndThrow();
		if (queued == 0)
			return;

		alSourcePlay(music.source);
//		AL_CheckAndThrow();
	}

}

int A_InitMUS() {

	ALsizei i;

	// clear any al errors
	alGetError();

	/* Rewind the source position and clear the buffer queue */
	alSourceRewind(music.source);
	alSourcei(music.source, AL_BUFFER, 0);

	/* Fill the buffer queue */
	for (i = 0; i < MAX_BUFFERS; i++)
	{
		/* Get some data to give it to the buffer */
		sf_count_t slen = sf_readf_short(music.sndfile, music.membuf, BUFFER_SIZE);
		if (slen < 1) break;

		slen *= music.sfinfo.channels * (sf_count_t)sizeof(short);
		alBufferData(music.buffers[i], music.format, music.membuf, (ALsizei)slen, music.sfinfo.samplerate);
	}
	if (alGetError() != AL_NO_ERROR)
	{
		printf("Error buffering for playback\n");
	}

	/* Now queue and start playback! */
	alSourceQueueBuffers(music.source, i, music.buffers);
	alSourcePlay(music.source);
	if (alGetError() != AL_NO_ERROR)
	{
		printf("Error starting playback\n");
	}
	return 0;

}

int A_PlayMUS(const char* filename) {

	A_LoadMUS(filename);
	A_InitMUS();
	return 0;

}

int A_StreamMUS() {

//	while (mixer.state == AL_PLAYING && alGetError() == AL_NO_ERROR) {
		A_UpdateMUS();
		alGetSourcei(music.source, AL_SOURCE_STATE, &mixer.state);
//	}
	if (!A_IsPlaying(music.source)) {
		sf_seek(music.sndfile, 0, 0);
		A_InitMUS();
	}
	return 0;

}

int A_PlaySFX(const char* filename) {

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
