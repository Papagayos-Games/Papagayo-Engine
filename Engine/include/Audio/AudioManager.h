#pragma once
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <fmod.hpp>
#include <fmod_errors.h>
struct AudioManager {

    AudioManager();

    ~AudioManager();
    static AudioManager* getInstance();
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
    static AudioManager* instance_;

};

struct Vector3 {
    float x;
    float y;
    float z;
};

class AudioEngine {
public:
    static void Init();
    static void Update();
    static void Shutdown();
    static int ErrorCheck(FMOD_RESULT result);

    void LoadSound(const std::string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
    void UnLoadSound(const std::string& strSoundName);
    void Set3dListenerAndOrientation(const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
    int  PlaySound(const std::string& strSoundName, const char* groupName = nullptr, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
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
    void mute();


};






int main(int argc, char* argv[])
{

    AudioEngine aEngine = AudioEngine();
    aEngine.Init();
    aEngine.PlaySound("swish.wav", nullptr, { 0,0,0 }, 10);

    bool isPlaying = false;
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        isPlaying = aEngine.IsPlaying(0);
        aEngine.Update();
    } while (isPlaying);

    aEngine.Shutdown();

    return 0;
}