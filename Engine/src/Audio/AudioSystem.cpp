#include "..\..\include\Audio\AudioSystem.h"
#include "AudioSystem.h"
#include <vector>
#include <iostream>
#include "Vector3.h"
#include <math.h>
#include <chrono>
#include <thread>
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
}

void AudioSystem::destroy() {
    instance_->clean();
    delete instance_;
}

AudioSystem::AudioSystem()
{
    mpSystem = NULL;
    errorCheck(FMOD::System_Create(&mpSystem));
    errorCheck(mpSystem->init(512, FMOD_INIT_NORMAL, nullptr));
}

AudioSystem::~AudioSystem()
{
    errorCheck(mpSystem->close());
    errorCheck(mpSystem->release());
}

void AudioSystem::update() {
    std::vector<ChannelMap::iterator> pStoppedChannels;
    for (auto it = instance_->mChannels.begin(), itEnd = instance_->mChannels.end(); it != itEnd; ++it)
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

        instance_->mChannels.erase(it);
    }
    errorCheck(instance_->mpSystem->update());
}

AudioSystem::SoundMap& AudioSystem::getSoundMap()
{
    return mSounds;
}

const AudioSystem::SoundMap& AudioSystem::getSoundMap() const
{
    return mSounds;
}

AudioSystem::ChannelMap& AudioSystem::getSoundChannels()
{
    return mChannels;
}

const AudioSystem::ChannelMap& AudioSystem::getSoundChannels() const
{
    return mChannels;
}

AudioSystem::ChannelGroupMap& AudioSystem::getChanGroupMap()
{
    return mGroup;
}

const AudioSystem::ChannelGroupMap& AudioSystem::getChanGroupMap() const
{
    return mGroup;
}

FMOD::System* AudioSystem::getSystem()
{
    return mpSystem;
}

FMOD::System* AudioSystem::getSystem() const
{
    return mpSystem;
}

int& AudioSystem::getNextChannelId()
{
    return mnNextChannelId;
}

const int& AudioSystem::getNextChannelId() const
{
    return mnNextChannelId;
}

void AudioSystem::init() {
    //AudioSystem::setupInstance(); // TO DO
}

//Comprueba si hay un error en la ejecucion de comando fmod
int AudioSystem::errorCheck(FMOD_RESULT result)
{
    if (result != FMOD_OK) {
        std::cout << "FMOD ERROR " << result << std::endl;
        return 1;
    }
    return 0;
}
/// <summary>
/// Carga un sonido en el sistema 
/// </summary>
/// <param name="strSoundName"> string del archivo </param>
/// <param name="b3d"> bool 3d /2d</param>
/// <param name="bLooping">bool bool on /off</param>
/// <param name="bStream">bool stream /compresses sample</param>
void AudioSystem::loadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
    auto encontrado = instance_->getSoundMap().find(strSoundName);
    if (encontrado != instance_->getSoundMap().end())
        return;


    FMOD_MODE eMode = FMOD_DEFAULT;
    eMode |= b3d ? FMOD_3D : FMOD_2D;
    eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
    eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

    FMOD::Sound* pSound = nullptr;
    errorCheck(instance_->getSystem()->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
    if (pSound) {
        instance_->getSoundMap()[strSoundName] = pSound;
    }

}
/// <summary>
/// Libera un sonido del sistema
/// </summary>
/// <param name="strSoundName"></param>
void AudioSystem::unloadSound(const std::string& strSoundName)
{
    auto encontrado = instance_->getSoundMap().find(strSoundName);
    if (encontrado == instance_->getSoundMap().end())
        return;
    errorCheck(encontrado->second->release());
    instance_->getSoundMap().erase(encontrado);
}
/// <summary>
/// NO IMPLEMENTADO
/// </summary>
/// <param name="vPos"></param>
/// <param name="fVolumedB"></param>
void AudioSystem::set3dListenerAndOrientation(const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB)
{   
}
/// <summary>
/// Reproduce un sonido , si no existe lo carga 
/// </summary>
/// <param name="strSoundName">nombre del archivo </param>
/// <param name="vPos">posicion</param>
/// <param name="groupName">nombre del grupo perteneciente si es null lo crea al general </param>
/// <param name="fVolumedB"> volumen </param>
/// <returns></returns>
int AudioSystem::playSound(const std::string& strSoundName, const Vector3& vPos = Vector3{ 0, 0, 0 }, const char* groupName,  float fVolumedB)
{
    int nChannelId = instance_->getNextChannelId()++;
    auto encontrado = instance_->getSoundMap().find(strSoundName);
    if (encontrado == instance_->getSoundMap().end())
    {
        loadSound(strSoundName);
        encontrado = instance_->getSoundMap().find(strSoundName);
        if (encontrado == instance_->getSoundMap().end())
        {
            return nChannelId;
        }
    }
    FMOD::Channel* pChannel = nullptr;
    FMOD::ChannelGroup* pGruoup = nullptr;
    if (instance_->getChanGroupMap().count(groupName) == 0 && groupName != nullptr)
    {
        pGruoup = createChannelGroup(groupName);
    }
    errorCheck(instance_->getSystem()->playSound(encontrado->second
        , pGruoup, true, &pChannel));
    if (pChannel)
    {
        FMOD_MODE currMode;
        encontrado->second->getMode(&currMode);
        if (currMode & FMOD_3D) {
            FMOD_VECTOR position = vectorToFmod(vPos);
            errorCheck(pChannel->set3DAttributes(&position, nullptr));
        }
        errorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
        errorCheck(pChannel->setPaused(false));
        instance_->getSoundChannels()[nChannelId] = pChannel;
    }
    return nChannelId;

}
//Para un canal
void AudioSystem::stopChannel(int nChannelId)
{

    auto encontrado = instance_->getSoundChannels().find(nChannelId);
    if (encontrado == instance_->getSoundChannels().end())
        return;
    errorCheck(encontrado->second->stop());
}
//Para todos los canales
void AudioSystem::stopAllChannels()
{

    for (auto x : instance_->getSoundChannels())
        errorCheck(x.second->stop());
}
//Coloca un canal en una posicion 3d 
void AudioSystem::setChannel3dPosition(int nChannelId, const Vector3& vPosition)
{
    auto encontrado = instance_->getSoundChannels().find(nChannelId);
    if (encontrado == instance_->getSoundChannels().end())
        return;

    FMOD_VECTOR position = vectorToFmod(vPosition);
    errorCheck(encontrado->second->set3DAttributes(&position, NULL));
}
//Devuelve true si un canal esta reproduciendose
bool AudioSystem::isPlaying(int nChannelId) const
{
    auto encontrado = instance_->getSoundChannels().find(nChannelId);
    if (encontrado == instance_->getSoundChannels().end())
        return false;
    bool isplay = false;
    errorCheck(instance_->getSoundChannels().at(nChannelId)->isPlaying(&isplay));
    return isplay;
}
//Si esta pausado el canal lo resume y si esta sonando lo pausa
void AudioSystem::pause_Resume_Channel(int nChannelId)
{
    auto encontrado = instance_->getSoundChannels().find(nChannelId);
    if (encontrado == instance_->getSoundChannels().end())
        return;
    bool ch = false;
    errorCheck(instance_->getSoundChannels().at(nChannelId)->getPaused(&ch));
    errorCheck(instance_->getSoundChannels().at(nChannelId)->setPaused(!ch));

}
//Convierte un vector fmod
FMOD_VECTOR& AudioSystem::vectorToFmod(const Vector3& vPosition)
{
    FMOD_VECTOR fVec;
    fVec.x = vPosition.x;
    fVec.y = vPosition.y;
    fVec.z = vPosition.z;
    return fVec;
}
//Crea un grupo de canales
FMOD::ChannelGroup* AudioSystem::createChannelGroup(const char* name)
{
    FMOD::ChannelGroup* channelGroup = nullptr;
    errorCheck(instance_->getSystem()->createChannelGroup(name, &channelGroup));
    instance_->getChanGroupMap()[name] = channelGroup;
    return channelGroup;
}
//Mutea un grupo de canales especifico  
void AudioSystem::muteChannelGroup(const char* name)
{
    bool mute = false;
    errorCheck(instance_->getChanGroupMap()[name]->getMute(&mute));
    errorCheck(instance_->getChanGroupMap()[name]->setMute(!mute));

}

float  AudioSystem::dbToVolume(float dB)
{
    return powf(10.0f, 0.05f * dB);
}

float  AudioSystem::volumeTodb(float volume)
{
    return 20.0f * log10f(volume);
}

//Cambia el volumen del canal 
void AudioSystem::setChannelvolume(int nChannelId, float fVolumedB)
{
    auto encontrado = instance_->getSoundChannels().find(nChannelId);
    if (encontrado == instance_->getSoundChannels().end())
        return;

    errorCheck(encontrado->second->setVolume(dbToVolume(fVolumedB)));
}