#include "AudioManager.h"

#include "fmod.hpp"
#include <fmod_errors.h>
#include <fmod.h>

AudioManager* AudioManager::instance_ = nullptr;

AudioManager* AudioManager::getInstance()
{
	if (instance_ == nullptr)
		return nullptr;

	return instance_;
}

bool AudioManager::setupInstance()
{
     //mpSystem = NULL;
	if (instance_ == nullptr) {
		instance_ = new AudioManager();
		return true;
	}

	return false;
}

void AudioManager::clean()
{
	delete instance_;
}
//

void AudioManager::Loadsound(const std::string& strSoundName)
{
	FMOD::Sound* sound;
	system_->createSound(
		strSoundName.c_str(),	// path al archivo de sonido
		FMOD_DEFAULT,	// valores (por defecto en este caso: sin loop, 2D)
		0,				// informacion adicional (nada en este caso)
		&sound);		// handle al buffer de sonido
}

void AudioManager::update()
{

 vector<ChannelMap::iterator> pStoppedChannels;
    for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
    {
        bool bIsPlaying = false;
        it->second->isPlaying(&bIsPlaying);
        if (!bIsPlaying)
        {
             pStoppedChannels.push_back(it);
        }
    }
    for (auto& it : pStoppedChannels)
    {
         mChannels.erase(it);
    }

}

float  AudioManager::dbToVolume(float dB)
{
    return powf(10.0f, 0.05f * dB);
}

float  AudioManager::VolumeTodB(float volume)
{
    return 20.0f * log10f(volume);
}


int AudioManager::ErrorCheck(FMOD::FMOD_RESULT result) {
    if (result != FMOD::FMOD_OK){
        cout << "FMOD ERROR " << result << endl;
        return 1;
    }
    // cout << "FMOD all good" << endl;
    return 0;
}

void AudioManager::PlaySound(const std::string& strSoundName, float volume, float pitch, bool loop)
{
	FMOD::Channel* channel;

	system_->playSound(
		sound,		// buffer que se "engancha" a ese canal
		0,			// grupo de canales, 0 sin agrupar (agrupado en el master)
		false,		// arranca sin "pause" (se reproduce directamente)
		&channel));	// devuelve el canal que asigna// el sonido ya se esta reproduciendo

	channel->setVolume(volume);
	channel->setPitch(pitch);
	channel.


}
//