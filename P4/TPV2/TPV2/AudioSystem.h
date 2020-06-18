#pragma once
#include "System.h"
#include "SDLAudioManager.h"
#include <string>


class AudioSystem :
    public System
{
public:
    AudioSystem() :System(ecs::_sys_Audio) { audioManager_ = new SDLAudioManager(); };
    ~AudioSystem() { delete audioManager_; };


    virtual void recieve(const msg::Message& msg) override;
    
private:
    SDLAudioManager* audioManager_;
};