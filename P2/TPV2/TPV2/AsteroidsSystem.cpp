#include "AsteroidsSystem.h"

void AsteroidsSystem::addAsteroids(int n)
{
	for (auto i(0u); i < n; i++) {
		int pared = game_->getRandGen()->nextInt(0, 3); //numero entre 0 y 3 ambos incluidos
		Vector2D p;
		int pos;

		switch (pared)
		{
		case 0: //borde izquierdo
			pos = rand() % windowHeight_;
			p = Vector2D(0, pos);
			break;
		case 1: //borde derecho
			pos = rand() % windowHeight_;
			p = Vector2D(windowWidth_, pos);
			break;
		case 2: //borde arriba
			pos = rand() % windowWidth_;
			p = Vector2D(pos, 0);
			break;
		case 3: //borde abajo
			pos = rand() % windowWidth_;
			p = Vector2D(pos, windowHeight_);
			break;
		default:
			break;
		}

		int r = game_->getRandGen()->nextInt(1, 2);

		Vector2D c = Vector2D(windowWidth_ / 2, windowHeight_ / 2) + Vector2D((game_->getRandGen()->nextInt(0, 100)) - 50,
			(game_->getRandGen()->nextInt(0, 100) % 100) - 50);
		Vector2D vel = (c - p).normalize() * ((game_->getRandGen()->nextInt(0, 9) + 1) / 10.0);

		Entity* e = mngr_->addEntity<AsteroidsPool>(p.getX(), p.getY(), r, vel, game_->getRandGen()->nextInt(1, 3));
		if (e != nullptr)
			e->addToGroup(ecs::_grp_Asteroid);

	}
}

void AsteroidsSystem::init()
{
	windowWidth_ = game_->getWindowWidth();
	windowHeight_ = game_->getWindowHeight();
}

void AsteroidsSystem::update()
{

	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		if (!e->isActive()) return; //si no esta activa pasa a la siguiente

		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		auto* rot = e->getComponent<Rotation>(ecs::Rotation);
		tr->position_ = tr->position_ + tr->velocity_;
		tr->rotation_ += rot->rotation_;

	}
}

void AsteroidsSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_FIGHTERASTEROID_COLLISION_: {
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) { //desactiva todos los asteroides
			if (!e->isActive()) return; //si no esta activa pasa a la siguiente
			e->setActive(false); //desactiva el asteroide
		}
		game_->getAudioMngr()->playChannel(Resources::Explosion, 0);
		game_->getAudioMngr()->pauseMusic();
		break;
	}
	case msg::_BULLETASTEROID_COLLISION_: { //dividir en dos/desactivar entidad
		Entity* asteroid = static_cast<const msg::BulletAsteroidCollisionMsg&>(msg).asteroid;
		int gen = asteroid->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime)->GetGen();

		if (gen > 0) { //aparecen dos mas
			Transform* tr = asteroid->getComponent<Transform>(ecs::Transform);
			int proxGen = gen - 1;
			for (int i = 0; i < 2; i++) {
				Vector2D v = tr->velocity_.rotate(i * 45);
				Vector2D p = tr->position_ + v.normalize();
				
				Entity* e = mngr_->addEntity<AsteroidsPool>(p.getX(), p.getY(), game_->getRandGen()->nextInt(1, 2), v,proxGen);
				if (e != nullptr)
					e->addToGroup(ecs::_grp_Asteroid);
			}
		}
		game_->getAudioMngr()->playChannel(Resources::Explosion, 0);
		asteroid->setActive(false);

		break;
	}
	default:
		break;
	}
}
