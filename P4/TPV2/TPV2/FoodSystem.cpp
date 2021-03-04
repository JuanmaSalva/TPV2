#include "FoodSystem.h"

#include "System.h"
#include "Entity.h"
#include "FoodPool.h"
#include "GameCtrlSystem.h"
#include "GameState.h"
#include "Manager.h"
#include "SDLGame.h"
#include "SDL_macros.h"

FoodSystem::FoodSystem() :
	System(ecs::_sys_Food), //
	numOfFoodPieces_(0) {
}

void FoodSystem::init() {
}

void FoodSystem::update() {
}

void FoodSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_ADD_FOOD: {
		const msg::AddFoodMSG& m = static_cast<const msg::AddFoodMSG&>(msg);
		addFood(m.num, m.foodType);
		break;
	}
	case msg::_DISABLE_CHERRIES:
		disableAll();
		break;
	case msg::_ON_EAT_FOOD: {
		const msg::OnEatFood& m = static_cast<const msg::OnEatFood&>(msg);
		onEat(m.entity, m.foodType);
		break;
	}
	default:
		break;
	}
}

void FoodSystem::onEat(Entity* e, int foodType) {
	// update score
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameStateEntity)->getComponent<GameState>(ecs::GameState);
	gameState->score_++;

	if ((foodType == 1 && mngr_->getGroupEntities(ecs::_grp_Cherry).size() > 0) ||  //aun quedan cerezas
		(foodType == 2 && (mngr_->getGroupEntities(ecs::_grp_Cherry).size() > 0 ||
		mngr_->getGroupEntities(ecs::_grp_Strawberry).size() > 0))) { //aun quedan peras
		mngr_->send<msg::Message>(msg::_EATEN_WRONG_FOOD);
	}

	mngr_->send<msg::PlayChannel>(Resources::PacMan_Eat, 0);
	//game_->getAudioMngr()->playChannel(Resources::PacMan_Eat, 0);

	// disbale food
	e->setActive(false);
	numOfFoodPieces_--;

	if (numOfFoodPieces_ == 0)
		mngr_->send<msg::Message>(msg::_NO_MORE_FOOD);
}

void FoodSystem::addFood(std::size_t n, int foodType) {
	RandomNumberGenerator* r = game_->getRandGen();

	// ghost width and height
	int width = 30;
	int height = 30;

	for (auto i(0u); i < n; i++) {

		int x = r->nextInt(10, game_->getWindowWidth() - width - 10);
		int y = r->nextInt(10, game_->getWindowHeight() - height - 10);
		Vector2D p(x, y);
		// add the entity
		Entity* e = mngr_->addEntity<FoodPool>(p, 30, 30);

		if (e != nullptr) {

			auto animatedImage = e->addComponent<AnimatedImageComponent>();
			animatedImage->reset();
			animatedImage->setFrameTime(100);
			Texture* spritesTex =
				SDLGame::instance()->getTextureMngr()->getTexture(
					Resources::PacManSprites);

			if (foodType == 0) {
				animatedImage->addFrame(spritesTex, { 128 * 4, 128, 128, 128 });
				e->addToGroup(ecs::_grp_Cherry);
			}
			else if (foodType == 1) {
				animatedImage->addFrame(spritesTex, { 768, 128, 128, 128 });
				e->addToGroup(ecs::_grp_Strawberry);
			}
			else if (foodType == 2) {
				animatedImage->addFrame(spritesTex, { 896, 128, 128, 128 });
				e->addToGroup(ecs::_grp_Pear);
			}

			numOfFoodPieces_++;
		}
	}
}

void FoodSystem::disableAll() {
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Cherry)) {
		e->setActive(false);
	}
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Strawberry)) {
		e->setActive(false);
	}
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Pear)) {
		e->setActive(false);
	}

	numOfFoodPieces_ = 0;
}
