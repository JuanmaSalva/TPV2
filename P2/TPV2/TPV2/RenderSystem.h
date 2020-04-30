#pragma once
#include "ecs.h"
#include "Manager.h"
#include "ImageComponent.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"
#include "Score.h"
#include "SDLGame.h"
#include "Texture.h"
#include "Health.h"

class RenderSystem : public System {
public:
	RenderSystem() :
		System(ecs::_sys_Render), heartTexture_(nullptr) {

	}

	void draw(Entity* e) {
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent* img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest =
			RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_);
	}

	void draw(Entity* e, SDL_Rect clip) {
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent* img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest =
			RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_, clip);
	}

	void drawScore() {
		auto sc = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2, 10);

	}

	void init() override {
		heartTexture_ = game_->getTextureMngr()->getTexture(Resources::Heart);
	}

	void update() override {
		// draw asteroids
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			draw(e);
		}

		//draw bullets
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			draw(e);
		}

		//draw fighter
		SDL_Rect dest = RECT(790, 100, 379, 284);
		draw(mngr_->getHandler(ecs::_hdlr_Fighter), dest);

		// draw score
		drawScore();

		// info message
		if (!mngr_->getGameState()->getTerminado() && mngr_->getGameState()->getParado()) {
			Texture msg(game_->getRenderer(), "Press ENTER to play", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
			msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 10);
		}
		else if (mngr_->getGameState()->getParado()){
			Texture msgGO(game_->getRenderer(), "Game over", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
			msgGO.render(game_->getWindowWidth() / 2 - msgGO.getWidth() / 2, game_->getWindowHeight() - msgGO.getHeight() - 100);

			Texture msg(game_->getRenderer(), "Press ENTER to play", game_->getFontMngr()->getFont(Resources::ARIAL24), { COLOR(0xff0000ff) });
			msg.render(game_->getWindowWidth() / 2 - msg.getWidth() / 2, game_->getWindowHeight() - msg.getHeight() - 10);
		}

		//draw health
		int playerHealth = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health)->getHealth();
		for (int i = 0; i < playerHealth; i++) {
			heartTexture_->render(SDL_Rect{ 10 + (35 * i), 10, 30, 30 }); //el 35*i es una manera de espaciarlos horizontalmente
		}
	}
private:
	Texture* heartTexture_;
};

