#include "CollisionSystem.h"

#include "Collisions.h"
#include "BulletsSystem.h"
#include "FighterInfo.h"
#include "GameCtrlSystem.h"
#include "Transform.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
		System(ecs::_sys_Collision) {
}

CollisionSystem::~CollisionSystem() {
}

void CollisionSystem::update() {
	auto gameCtrlSys = mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl);

	if (gameCtrlSys->getState() != GameCtrlSystem::RUNNING)
		return;


	bool roundOver = false;

	for (auto &f : mngr_->getGroupEntities(ecs::_grp_Fighters)) {
		auto fTR = f->getComponent<Transform>(ecs::Transform);

		for (auto &b : mngr_->getGroupEntities(ecs::_grp_Bullets)) {
			if (!b->isActive())
				continue;

			auto bTR = b->getComponent<Transform>(ecs::Transform);

			if (Collisions::collidesWithRotation(bTR->position_, bTR->width_,
					bTR->height_, bTR->rotation_, fTR->position_, fTR->width_,
					fTR->height_, fTR->rotation_)) {

				roundOver = true;
				auto id = f->getComponent<FighterInfo>(ecs::FighterInfo)->fighterId;
				mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath(id);

				mngr_->send<msg::FighterCollision>(id);
			}
		}
	}

	auto fighters = mngr_->getGroupEntities(ecs::_grp_Fighters);
	Transform* trF1 = fighters[0]->getComponent<Transform>(ecs::Transform);
	Transform* trF2 = fighters[1]->getComponent<Transform>(ecs::Transform);
	if (Collisions::collidesWithRotation(trF1->position_, trF1->width_,
		trF1->height_, trF1->rotation_, trF2->position_, trF2->width_,
		trF2->height_, trF2->rotation_)) { //colision entre cazas
		mngr_->send<msg::Message>(msg::_FIGHTERS_COLLIDE);

	}

	if ( roundOver )
		mngr_->getSystem<BulletsSystem>(ecs::_sys_Bullets)->disableAll();
}

