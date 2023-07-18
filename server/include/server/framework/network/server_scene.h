#pragma once
#ifndef __SERVER_SCENE_H__
#define __SERVER_SCENE_H__

#include "engine/framework/framework.h"

class CServer;
class CServerScene {
protected:
	CServer& server;

public:
	CServerScene(CServer& server);
	~CServerScene();

	CServer& GetServer() { return server; }

	virtual bool ProcessPacket(std::shared_ptr<CPacket> packet) = 0;
	virtual void OnConnect(ClientID id) = 0;
	virtual void OnDisconnect(ClientID id) = 0;
};
typedef CServerScene* pServerScene;

#endif // !__SERVER_SCENE_H__
