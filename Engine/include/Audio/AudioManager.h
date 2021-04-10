#pragma once

#include <string>
#include <map>

namespace FMOD {
	class ChannelGroup;
	class Channel;
	class Sound;
	class System;
	//
    typedef std::map<std::string, FMOD::Sound*> SoundMap;
    typedef std::map<int, FMOD::Channel*> ChannelMap;
	//
}



class AudioManager {
public:
	~AudioManager();
	static AudioManager* getInstance();
	static bool setupInstance();
	static void clean();
	//
    static int ErrorCheck(FMOD_RESULT result);
	//
	    void Loadsound(const std::string& strSoundName);
		void UnLoadSound(const std::string& strSoundName);
		void PlaySound(const std::string& strSoundName, float volume, float pitch, bool loop);
		void StopChannel(int nChannelId);
		void StopAllChannels();
		bool IsPlaying(int nChannelId) const;
		void SetChannelvolume(int nChannelId, float fVolumedB);
		float dbToVolume(float db);
        float VolumeTodb(float volume);

		void Update();

private:
	static AudioManager* instance_;
	std::map<std::string, FMOD::Sound*> sounds_;
    FMOD::System* system_ = nullptr;
	//
	int mnNextChannelId;
	FMOD::SoundMap mSounds;
    FMOD::ChannelMap mChannels;
	//



};
