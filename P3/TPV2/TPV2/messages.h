#pragma once
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>

namespace msg {

	using msgSizeType = uint32_t;

	enum MsgId : uint8_t {
		_CONNECTED, //
		_CONNECTION_REFUSED, //
		_CLIENT_DISCONNECTED, //
		_SECOND_PLAYER_JOINED,
		_ASK_GAME_TO_START,
		_GAME_STARTED,
		_BULLET_SHOT,

		//
		_last_MsgId_
	};

#pragma pack(push,1)

	struct Message {
		Message(msgSizeType size, MsgId id) :
			size(size), senderClientId(0), id(id) {
		}
		Message(MsgId id) :
			Message(sizeof(Message), id) {
		}
		msgSizeType size;
		uint32_t senderClientId;
		MsgId id;
	};

	struct ConnectedMsg : Message {
		ConnectedMsg(int clientId) :
			Message(sizeof(ConnectedMsg), _CONNECTED), clientId(clientId) {
		}
		uint32_t clientId;
	};

	struct ClientDisconnectedMsg : Message {
		ClientDisconnectedMsg(uint32_t clientId) :
			Message(sizeof(ClientDisconnectedMsg), _CLIENT_DISCONNECTED), clientId(
				clientId) {
		}
		uint32_t clientId;
	};

	struct BulletShot :Message
	{
		BulletShot(int pX, int pY, int vX, int vY):Message(sizeof(BulletShot), _BULLET_SHOT), posX(pX),posY(pY), velX(vX), velY(vY) {
		}
		uint32_t posX, posY, velX, velY;
	};


#pragma pack(pop)

}
