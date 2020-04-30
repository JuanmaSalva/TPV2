#pragma once
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "Transform.h"
#include "Rotation.h"

class BulletPool: public Singleton<BulletPool>
{
	friend Singleton<BulletPool>;
public:
	~BulletPool();

	static void destroy(Entity* p);
	Entity* construct_(Vector2D pos, Vector2D vel, double width, double height);
	void destroy_(Entity* p);

	template<typename ...Targs>
	static Entity* construct(Targs&&...args) {
		return BulletPool::instance()->construct_(std::forward<Targs>(args)...);
	}


private:
	BulletPool();
	BulletPool(std::size_t n);

	ObjectPool<Entity> pool_;
};

