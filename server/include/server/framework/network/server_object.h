#pragma once
#ifndef __SERVER_OBJECT_H__
#define __SERVER_OBJECT_H__

#include "engine/framework/framework.h"

class CServerScene;
class CServerObject {
protected:
	CServerScene& server_scene;

public:
	CServerObject(CServerScene& server_scene) : server_scene(server_scene) {};
	virtual ~CServerObject() = 0 {};

	CServerScene& GetServerScene() { return server_scene; }

	virtual void Load(float position_x, float position_y, json& data) = 0;
	virtual void PackLoadPacket(pPacket packet) = 0;
};
typedef CServerObject* pServerObject;

#endif // !__SERVER_OBJECT_H__
