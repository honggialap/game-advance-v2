#pragma once
#ifndef __CLIENT_SCENE_H__
#define __CLIENT_SCENE_H__

#include "engine/framework/network/packet.h"

class CClient;
class CClientScene {
protected:
	CClient& client;

public:
	CClientScene(CClient& client);
	~CClientScene();

	CClient& GetClient() { return client; }

	virtual void OnConnect() = 0;
	virtual void OnDisconnect() = 0;
	virtual void OnConnectFail() = 0;

	virtual bool ProcessPacket(std::shared_ptr<CPacket> packet) = 0;
};
typedef CClientScene* pClientScene;

#endif // !__CLIENT_SCENE_H__
