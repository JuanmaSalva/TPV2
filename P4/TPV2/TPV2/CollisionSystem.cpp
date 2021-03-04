#include "CollisionSystem.h"

#include "Collisions.h"
#include "FoodSystem.h"
#include "GameState.h"
#include "GhostsSystem.h"
#include "Manager.h"

CollisionSystem::CollisionSystem() :
	System(ecs::_sys_Collisions) {
}

void CollisionSystem::update() {
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameStateEntity)->getComponent<GameState>(ecs::GameState);
	if (gameState->state_ != GameState::RUNNING)
		return;

	auto ptr = mngr_->getHandler(ecs::_hdlr_PacManEntity)->getComponent<Transform>(ecs::Transform);

	// collision with cherry
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Cherry)) {
		collision(e, ptr, 0);
	}
	// collision with strawberry
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Strawberry)) {
		collision(e, ptr, 1);
	}
	// collision with pear
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Pear)) {
		collision(e, ptr, 2);
	}


	// collision with ghosts
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Ghost)) {
		auto etr = e->getComponent<Transform>(ecs::Transform);
		if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_,
			etr->position_, etr->width_, etr->height_)) {
			mngr_->send<msg::Message>(msg::_COLLISION_PAC_MAN);
			break;
		}
	}
}

void CollisionSystem::collision(Entity* e, Transform* ptr, int foodType)
{
	auto etr = e->getComponent<Transform>(ecs::Transform);
	if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_,
		etr->position_, etr->width_, etr->height_)) {
		mngr_->send<msg::OnEatFood>(e, foodType);
	}
}
