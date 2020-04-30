#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "StarsSystem.h"
#include "Transform.h"

class CollisionSystem : public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update() { //HAY QUE CAMBIARLO MUCHO	

		auto fighterTr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);//puntero al componente transform del caza
		vector<Entity*> balas = mngr_->getGroupEntities(ecs::_grp_Bullet);

		for (auto& asteroide : mngr_->getGroupEntities(ecs::_grp_Asteroid)) { //recorre todos los asteroides
			auto asterTr = asteroide->getComponent<Transform>(ecs::Transform);
			if (Collisions::collides(fighterTr->position_, fighterTr->width_, fighterTr->height_, asterTr->position_, asterTr->width_, asterTr->height_)) { //hay una colisoin
				mngr_->send(msg::AsteroidFighterCollisionMsg(mngr_->getHandler(ecs::_hdlr_Fighter), asteroide));//envia el mensaje
			}

			for (auto& bala : balas) {
				auto balaTr = bala->getComponent<Transform>(ecs::Transform);
				if (Collisions::collides(asterTr->position_, asterTr->width_, asterTr->height_, balaTr->position_, balaTr->width_, balaTr->height_)) { //hay una colisoin
					mngr_->send(msg::BulletAsteroidCollisionMsg(asteroide, bala));//envia el mensaje
				}
			}
		}
	}
};
