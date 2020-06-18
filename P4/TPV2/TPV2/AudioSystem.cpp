#include "AudioSystem.h"

void AudioSystem::init()
{
	audioManager_ = new SDLAudioManager();
	audioManager_->init();

	for (auto& sound : Resources::sounds_) {
		audioManager_->loadSound(sound.id, sound.fileName);
	}

	for (auto& music : Resources::musics_) {
		audioManager_->loadMusic(music.id, music.fileName);
	}
}

void AudioSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_HALT_MUSIC:
		audioManager_->haltMusic();
		break;
	case msg::_PLAY_MUSIC: {
		const msg::PlayMusic& m = static_cast<const msg::PlayMusic&>(msg);
		audioManager_->playMusic(m.musicId, -1);
		break;
	}
	case msg::_PLAY_CHANNEL: {
		const msg::PlayChannel& m = static_cast<const msg::PlayChannel&>(msg);
		audioManager_->playChannel(m.audioId,0,m.channel);
		
		break;
	}
	default:
		break;
	}
}