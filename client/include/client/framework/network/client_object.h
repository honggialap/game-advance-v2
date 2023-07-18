#pragma once
#ifndef __CLIENT_OBJECT_H__
#define __CLIENT_OBJECT_H__

#include "engine/framework/framework.h"

class CClientScene;
class CClientObject {
protected:
	CClientScene& server_scene;

public:
	CClientObject(CClientScene& server_scene) : server_scene(server_scene) {};
	virtual ~CClientObject() = 0 {};

	CClientScene& GetServerScene() { return server_scene; }

	virtual void LoadFromPacket(pPacket packet) = 0;
	virtual void HandleStatePacket(pPacket packet) = 0;
};
typedef CClientObject* pClientObject;

#endif // !__CLIENT_OBJECT_H__
