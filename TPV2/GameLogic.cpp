#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic():Component(ecs::GameLogic) //llama a la constructora de component
{
}

GameLogic::GameLogic(Transform* ballTR, Transform* leftPaddleTR,
	Transform* rightPaddleTR) :
	Component(ecs::GameLogic), //
	ballTR_(ballTR), //
	leftPaddleTR_(leftPaddleTR), //
	rightPaddleTR_(rightPaddleTR), //
	scoreManager_(nullptr) //
{
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
	// scoreManager_ = GETCMP2(ecs::ScoreManager,ScoreManager);
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() {

}

