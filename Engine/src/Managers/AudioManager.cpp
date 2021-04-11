#pragma unmanaged

#include "fmod.h"
#include "fmod_errors.h"
//#include ".\SoundManager.h"

SoundManager::SoundManager(void)
{
	FSOUND_SetOutput(FSOUND_OUTPUT_DSOUND);
	FSOUND_SetDriver(0);
	FSOUND_SetMixer(FSOUND_MIXER_AUTODETECT);
	FSOUND_Init(44100, 32, 0);
}

SoundManager::~SoundManager(void)
{
	FSOUND_Close();
}

void SoundManager::update()
{
	FSOUND_Update();
}