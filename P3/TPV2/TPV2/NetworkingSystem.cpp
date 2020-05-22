#include "NetworkingSystem.h"

#include "messages.h"
#include "Manager.h"
#include "GameCtrlSystem.h"

NetworkingSystem::NetworkingSystem() :
		System(ecs::_sys_NetWorking) {

}

NetworkingSystem::~NetworkingSystem() {
}

void NetworkingSystem::recieve(const msg::Message &msg) {
	if (msg.senderClientId == mngr_->getClientId()) {
		game_->getNetworking()->send(msg);
	}
}

void NetworkingSystem::update() {
	auto net = game_->getNetworking();
	msg::Message *msg = nullptr;

	while ((msg = net->recieve()) != nullptr) {
		switch (msg->id) {			
		case msg::_CLIENT_DISCONNECTED:
			mngr_->forwardMsg<msg::ClientDisconnectedMsg>(msg->senderClientId,
					static_cast<msg::ClientDisconnectedMsg*>(msg)->clientId);
			break;
		case msg::_SECOND_PLAYER_JOINED:
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->setStateReady();
			break;
		case msg::_GAME_STARTED:
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->startGame();
			break;
		case msg::_ASK_GAME_TO_START:
			mngr_->send<msg::Message>(msg::_GAME_STARTED);
			mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->startGame();
			break;
		default:
			assert(false);
			break;
		}
	}

}
