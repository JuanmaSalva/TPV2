#pragma once
#include <cstddef>

class Entity;

namespace msg {

	using msgType = std::size_t;
	enum MsgId : msgType {
		_STARPACMAN_COLLISION_,


		_last_MsdId_
	};

	struct Message //version generica
	{
		Message(MsgId id) : id(id) {
		}

		MsgId id;
	};

	struct StarPacManCollisionMsg:Message
	{
		Entity* pcman;
		Entity* star;

		StarPacManCollisionMsg(Entity* p, Entity* s):Message(_STARPACMAN_COLLISION_),
			pcman(p), star(s){
		}
	};
}