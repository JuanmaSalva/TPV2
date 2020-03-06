#include "GameLogic.h"

GameLogic::GameLogic(AsteroidPool* a, BulletsPool* b, Health* h, Transform* t) : Component(ecs::GameLogic),
asterPool_(a), bulletsPool_(b), healtzCaza_(h), trCaza_(t), scoreMgr_(nullptr)
{
}

void GameLogic::init()
{
	scoreMgr_ = GETCMP1_(ScoreManager);
	poolAsteroid = asterPool_->getPool()->getPool();
	poolBullets = bulletsPool_->getPool()->getPool();
}

void GameLogic::update()
{
	if (!scoreMgr_->getParado()) {

		colisionAsteroidesCaza();
		colisionBalasAsteroides();
	}
}

void GameLogic::colisionAsteroidesCaza()
{
	for (int i = 0; i < poolAsteroid.capacity(); i++) {
		if (poolAsteroid[i]->inUse_) {
			if (Collisions::collidesWithRotation(poolAsteroid[i]->getPos(), poolAsteroid[i]->getScaleX(), poolAsteroid[i]->getScaleY(), poolAsteroid[i]->getRotation(),
				trCaza_->getPos(), trCaza_->getH(), trCaza_->getW(), trCaza_->getRot())) { //un asteroide ha colisionado con el caza

				asterPool_->disableAll();
				bulletsPool_->disablAll();
				healtzCaza_->loseLife();
				scoreMgr_->setParado(true);

				if (healtzCaza_->getLife() == 0) { //ha muerto del todo
					scoreMgr_->setTerminado(true);
				}

				trCaza_->setPos(Vector2D(game_->getWindowWidth() / 2 - trCaza_->getW() / 2, game_->getWindowHeight() / 2 - trCaza_->getH() / 2));
				trCaza_->setVel(Vector2D(0, 0));
				trCaza_->setRot(0);
			}
		}
	}
}


void GameLogic::colisionBalasAsteroides()
{
	for (int i = 0; i < poolBullets.capacity(); i++) {
		if (poolBullets[i]->inUse_) {
			for (int j = 0; j < poolAsteroid.capacity(); j++) {
				if (poolAsteroid[j]->inUse_ &&
					Collisions::collidesWithRotation(poolBullets[i]->getPos(), poolBullets[i]->getW(), poolBullets[i]->getH(), poolBullets[i]->getRot(),
						poolAsteroid[j]->getPos(), poolAsteroid[j]->getScaleX(), poolAsteroid[j]->getScaleY(), poolAsteroid[j]->getRotation()) &&
					poolBullets[i]->inUse_) {
					//ha colisionado una bala con un asteroide
					bulletsPool_->onCollision(poolBullets[i]);
					asterPool_->onCollision(poolAsteroid[j]);
					scoreMgr_->sumPoints(1);

					if(asterPool_->getNumOfAsteroid() == 0){
						scoreMgr_->setTerminado(true);
						scoreMgr_->setGanado(true);
						scoreMgr_->setParado(true);

						asterPool_->disableAll();
						bulletsPool_->disablAll();						

						healtzCaza_->resetLife();
						trCaza_->setPos(Vector2D(game_->getWindowWidth() / 2 - trCaza_->getW() / 2, game_->getWindowHeight() / 2 - trCaza_->getH() / 2));
						trCaza_->setVel(Vector2D(0, 0));
						trCaza_->setRot(0);
					}
				}
			}
		}
	}
}
