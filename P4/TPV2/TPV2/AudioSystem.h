#pragma once
#include "System.h"
#include "SDLAudioManager.h"
#include <string>


class AudioSystem :
    public System
{
public:
    AudioSystem() :System(ecs::_sys_Audio) {};
    ~AudioSystem() { delete audioManager_; };

    virtual void init();
    virtual void recieve(const msg::Message& msg) override;
    
private:
    SDLAudioManager* audioManager_;
};