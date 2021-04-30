#pragma once

#include <map>
#include <string>
class Vector3;
class vector;

#include "fmod.hpp"
#include "fmod_errors.h"
struct AudioSystem {

    AudioSystem();

    ~AudioSystem();
    static AudioSystem* getInstance();
    static bool setupInstance();
    static void clean();
    void Update();

    FMOD::System* mpSystem;

    int mnNextChannelId = 0;

    typedef std::map<std::string, FMOD::Sound*> SoundMap;
    typedef std::map<int, FMOD::Channel*> ChannelMap;
    typedef std::map<const char*, FMOD::ChannelGroup*> ChannelGroupMap;

    SoundMap mSounds;
    ChannelMap mChannels;
    ChannelGroupMap mGroup;
    static AudioSystem* instance_;

};


class AudioEngine {
public:
    static void Init();
    static void Update();
    static void Shutdown();
    static int ErrorCheck(FMOD_RESULT result);

    void LoadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
    void UnLoadSound(const std::string& strSoundName);
    void Set3dListenerAndOrientation(const Vector3& vPos, float fVolumedB = 0.0f);
    int  PlaySound(const std::string& strSoundName, const Vector3& vPos ,const char* groupName = nullptr, float fVolumedB = 0.0f);
    void StopChannel(int nChannelId);
    void StopAllChannels();
    void SetChannel3dPosition(int nChannelId, const Vector3& vPosition);
    void SetChannelvolume(int nChannelId, float fVolumedB);
    bool IsPlaying(int nChannelId) const;
    void Pause_Resume_Channel(int nChannelId);
    float dbToVolume(float db);
    float VolumeTodb(float volume);
    FMOD_VECTOR VectorToFmod(const Vector3& vPosition);
    FMOD::ChannelGroup* createChannelGroup(const char* name);
    void muteChannelGroup(const char* name);


};