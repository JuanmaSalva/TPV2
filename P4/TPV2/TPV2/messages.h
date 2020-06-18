#pragma once
#include <ctime>
#include "Resources.h"

class Entity;

namespace msg {

using msgType = std::size_t;

enum MsgId : msgType {
	_GAME_START, 
	_GAME_OVER,
	_PAC_MAN_DEATH,
	_COLLISION_PAC_MAN,
	_NO_MORE_FOOD,
	_ADD_FOOD,
	_ADD_GHOST,
	_DISABLE_GHOST,
	_DISABLE_CHERRIES,
	_RESET_PACMAN_POS,
	_ON_EAT_CHERRY,

	_PLAY_CHANNEL,
	_PLAY_MUSIC,
	_HALT_MUSIC,

	//
	_last_MsgId_
};

struct Message {
	Message(MsgId id) :
			id(id) {
	}
	MsgId id;
};


struct SingleIntMessage : Message
{
	SingleIntMessage(int n, MsgId id): Message(id) {
		num = n;
	}
	int num;
};

struct OnEatCherryMessage: Message
{
	OnEatCherryMessage(Entity* e) : Message(msg::_ON_EAT_CHERRY) {
		entity = e;
	}

	Entity* entity;
};

struct PlayMusic: Message
{
	PlayMusic(Resources::AudioId m) :Message(_PLAY_MUSIC) { 
		musicId = m; 
	};

	Resources::AudioId musicId;
};

struct PlayChannel : Message {
	PlayChannel(Resources::AudioId a, int c):Message(_PLAY_CHANNEL) {
		audioId = a;
		channel = c;
	}

	Resources::AudioId audioId;
	int channel;
};

}
