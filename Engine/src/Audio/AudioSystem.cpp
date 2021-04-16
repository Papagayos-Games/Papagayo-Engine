#include "AudioSystem.h"

AudioSystem* AudioSystem::instance_ = nullptr;

AudioSystem* AudioSystem::getInstance()
{
    if (instance_ == nullptr)
        return nullptr;

    return instance_;
}

bool AudioSystem::setupInstance()
{
    if (instance_ == nullptr) {
        instance_ = new AudioSystem();
        return true;
    }

    return false;
}



void AudioSystem::clean()
{
    delete instance_;
}



AudioSystem::AudioSystem()
{
    mpSystem = NULL;
    AudioEngine::ErrorCheck(FMOD::System_Create(&mpSystem));
    AudioEngine::ErrorCheck(mpSystem->init(512, FMOD_INIT_NORMAL, nullptr));
}

AudioSystem::~AudioSystem()
{
    AudioEngine::ErrorCheck(mpSystem->close());
    AudioEngine::ErrorCheck(mpSystem->release());
}

void AudioSystem::Update() {
    std::vector<ChannelMap::iterator> pStoppedChannels;
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
    AudioEngine::ErrorCheck(mpSystem->update());
}

void AudioEngine::Init() {
    AudioSystem::setupInstance();
}

void AudioEngine::Update() {
    AudioSystem::getInstance()->Update();
}


int AudioEngine::ErrorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cout << "FMOD ERROR " << result << std::endl;
        return 1;
    }
    return 0;
}

void AudioEngine::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
    auto encontrado = AudioSystem::getInstance()->mSounds.find(strSoundName);
    if (encontrado != AudioSystem::getInstance()->mSounds.end())
        return;


    FMOD_MODE eMode = FMOD_DEFAULT;
    eMode |= b3d ? FMOD_3D : FMOD_2D;
    eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

    FMOD::Sound* pSound = nullptr;
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
    if (pSound) {
        AudioSystem::getInstance()->mSounds[strSoundName] = pSound;
    }

}

void AudioEngine::UnLoadSound(const std::string& strSoundName)
{
    auto encontrado = AudioSystem::getInstance()->mSounds.find(strSoundName);
    if (encontrado == AudioSystem::getInstance()->mSounds.end())
        return;
    AudioEngine::ErrorCheck(encontrado->second->release());
    AudioSystem::getInstance()->mSounds.erase(encontrado);
}

void AudioEngine::Set3dListenerAndOrientation(const Vector3& vPos, float fVolumedB)
{
}

int AudioEngine::PlaySound(const std::string& strSoundName, const char* groupName, const Vector3& vPos, float fVolumedB)
{
    int nChannelId = AudioSystem::getInstance()->mnNextChannelId++;
    auto encontrado = AudioSystem::getInstance()->mSounds.find(strSoundName);
    if (encontrado == AudioSystem::getInstance()->mSounds.end())
    {
        LoadSound(strSoundName);
        encontrado = AudioSystem::getInstance()->mSounds.find(strSoundName);
        if (encontrado == AudioSystem::getInstance()->mSounds.end())
        {
            return nChannelId;
        }
    }
    FMOD::Channel* pChannel = nullptr;
    FMOD::ChannelGroup* pGruoup = nullptr;
    if (AudioSystem::getInstance()->mGroup.count(groupName) == 0 && groupName != nullptr)
    {
        pGruoup = createChannelGroup(groupName);
    }
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mpSystem->playSound(encontrado->second
        , pGruoup, true, &pChannel));
    if (pChannel)
    {
        FMOD_MODE currMode;
        encontrado->second->getMode(&currMode);
        if (currMode & FMOD_3D) {
            FMOD_VECTOR position = VectorToFmod(vPos);
            AudioEngine::ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
        }
        AudioEngine::ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
        AudioEngine::ErrorCheck(pChannel->setPaused(false));
        AudioSystem::getInstance()->mChannels[nChannelId] = pChannel;
    }
    return nChannelId;

}

void AudioEngine::StopChannel(int nChannelId)
{

    auto encontrado = AudioSystem::getInstance()->mChannels.find(nChannelId);
    if (encontrado == AudioSystem::getInstance()->mChannels.end())
        return;
    AudioEngine::ErrorCheck(encontrado->second->stop());
}

void AudioEngine::StopAllChannels()
{

    for (auto x : AudioSystem::getInstance()->mChannels)
        AudioEngine::ErrorCheck(x.second->stop());
}

void AudioEngine::SetChannel3dPosition(int nChannelId, const Vector3& vPosition)
{
    auto encontrado = AudioSystem::getInstance()->mChannels.find(nChannelId);
    if (encontrado == AudioSystem::getInstance()->mChannels.end())
        return;

    FMOD_VECTOR position = VectorToFmod(vPosition);
    AudioEngine::ErrorCheck(encontrado->second->set3DAttributes(&position, NULL));
}



bool AudioEngine::IsPlaying(int nChannelId) const
{
    auto encontrado = AudioSystem::getInstance()->mChannels.find(nChannelId);
    if (encontrado == AudioSystem::getInstance()->mChannels.end())
        return false;
    bool isplay = false;
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mChannels.at(nChannelId)->isPlaying(&isplay));
    return isplay;
}

void AudioEngine::Pause_Resume_Channel(int nChannelId)
{
    auto encontrado = AudioSystem::getInstance()->mChannels.find(nChannelId);
    if (encontrado == AudioSystem::getInstance()->mChannels.end())
        return;
    bool ch = false;
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mChannels.at(nChannelId)->getPaused(&ch));
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mChannels.at(nChannelId)->setPaused(!ch));

}

FMOD_VECTOR AudioEngine::VectorToFmod(const Vector3& vPosition)
{
    FMOD_VECTOR fVec;
    fVec.x = vPosition.x;
    fVec.y = vPosition.y;
    fVec.z = vPosition.z;
    return fVec;
}

FMOD::ChannelGroup* AudioEngine::createChannelGroup(const char* name)
{
    FMOD::ChannelGroup* channelGroup = nullptr;
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mpSystem->createChannelGroup(name, &channelGroup));
    AudioSystem::getInstance()->mGroup[name] = channelGroup;
    return channelGroup;
}

void AudioEngine::muteChannelGroup(const char* name)
{
    bool mute = false;
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mGroup[name]->getMute(&mute));
    AudioEngine::ErrorCheck(AudioSystem::getInstance()->mGroup[name]->setMute(!mute));

}

void AudioEngine::mute()
{
    //  for
}


float  AudioEngine::dbToVolume(float dB)
{
    return powf(10.0f, 0.05f * dB);
}

float  AudioEngine::VolumeTodb(float volume)
{
    return 20.0f * log10f(volume);
}

void AudioEngine::Shutdown() {
    AudioSystem::getInstance()->clean();

}

void AudioEngine::SetChannelvolume(int nChannelId, float fVolumedB)
{
    auto encontrado = AudioSystem::getInstance()->mChannels.find(nChannelId);
    if (encontrado == AudioSystem::getInstance()->mChannels.end())
        return;

    AudioEngine::ErrorCheck(encontrado->second->setVolume(dbToVolume(fVolumedB)));
}