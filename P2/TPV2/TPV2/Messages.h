#pragma once
#include <cstddef>

class Entity;

namespace msg {

	using msgType = std::size_t;
	enum MsgId : msgType {
		_FIGHTERASTEROID_COLLISION_,
		_BULLETASTEROID_COLLISION_,

		_last_MsdId_
	};

	struct Message //version generica
	{
		Message(MsgId id) : id(id) {
		}

		MsgId id;
	};

	struct AsteroidFighterCollisionMsg :Message
	{
		Entity* fighter;
		Entity* asteroid;

		AsteroidFighterCollisionMsg(Entity* f, Entity* a) :Message(_FIGHTERASTEROID_COLLISION_),
			fighter(f), asteroid(a) {
		}
	};

	struct BulletAsteroidCollisionMsg :Message
	{
		Entity* asteroid;
		Entity* bullet;

		BulletAsteroidCollisionMsg(Entity* a, Entity* b) :Message(_BULLETASTEROID_COLLISION_),
			asteroid(a), bullet(b) {

		}
	};
}