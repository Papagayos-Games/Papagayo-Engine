#pragma once

#ifndef AUDIO_AUDIOSYS
#define AUDIO_AUDIOSYS

#include <map>
#include <string>

#include "fmod.hpp"
#include "fmod_errors.h"

class Vector3;

class AudioSystem {
public:
    typedef std::map<std::string, FMOD::Sound*> SoundMap;
    typedef std::map<int, FMOD::Channel*> ChannelMap;
    typedef std::map<const char*, FMOD::ChannelGroup*> ChannelGroupMap;
private:
    AudioSystem();
    ~AudioSystem();
    void init();

    SoundMap mSounds;
    ChannelMap mChannels;
    ChannelGroupMap mGroup;

    FMOD::System* mpSystem;

    int mnNextChannelId = 0;

    static AudioSystem* instance_;
public:
    static AudioSystem* getInstance();
    static bool setupInstance();
    static void update();
    static void clean();
    static void destroy();

    SoundMap& getSoundMap();
    const SoundMap& getSoundMap() const;

    ChannelMap& getSoundChannels();
    const ChannelMap& getSoundChannels() const;

    ChannelGroupMap& getChanGroupMap();
    const ChannelGroupMap& getChanGroupMap() const;

    FMOD::System* getSystem();
    FMOD::System* getSystem() const;

    int& getNextChannelId();
    const int& getNextChannelId() const;

    static int errorCheck(FMOD_RESULT result);

    void loadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
    void unloadSound(const std::string& strSoundName);
    void set3dListenerAndOrientation(const Vector3& vPos, float fVolumedB = 0.0f);
    int  playSound(const std::string& strSoundName, const Vector3& vPos ,const char* groupName = nullptr, float fVolumedB = 0.0f);
    void stopChannel(int nChannelId);
    void stopAllChannels();
    void setChannel3dPosition(int nChannelId, const Vector3& vPosition);
    void setChannelvolume(int nChannelId, float fVolumedB);
    bool isPlaying(int nChannelId) const;
    void pause_Resume_Channel(int nChannelId);
    float dbToVolume(float db);
    float volumeTodb(float volume);
    FMOD_VECTOR& vectorToFmod(const Vector3& vPosition);
    FMOD::ChannelGroup* createChannelGroup(const char* name);
    void muteChannelGroup(const char* name);
};

#endif // !AUDIO_AUDIOSYS