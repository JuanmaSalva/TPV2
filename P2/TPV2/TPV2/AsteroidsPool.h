#pragma once
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "Transform.h"
#include "Rotation.h"
#include "AsteroidLifeTime.h"


class AsteroidsPool : public Singleton<AsteroidsPool>
{
	friend Singleton<AsteroidsPool>;
public:
	~AsteroidsPool();

	static void destroy(Entity* p);
	Entity* construct_(double x, double y, double r, Vector2D velocity, int gen);
	void destroy_(Entity* p);

	template<typename ...Targs>
	static Entity* construct(Targs&&...args) {
		return AsteroidsPool::instance()->construct_(std::forward<Targs>(args)...);
	}


private:
	AsteroidsPool();
	AsteroidsPool(std::size_t n);

	ObjectPool<Entity> pool_;
};

