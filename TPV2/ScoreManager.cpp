#include "ScoreManager.h"

ScoreManager::ScoreManager() : Component(ecs::ScoreManager),
running_(false), finished_(false), score_(0)
{

}

ScoreManager::~ScoreManager() {
}

