#pragma once
#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "common.h"

class CGameObjectManager;
class CGameObject {
private:
	CGameObjectManager& game_object_manager;

	GameObjectID id = INVALID_GAMEOBJECT_ID;
	std::string name;
	ActorType type = EActorType::INVALID_ACTOR;
	bool is_destroyed = false;

	std::string resource_path;

public:
	CGameObject(CGameObjectManager& game_object_manager, ActorType type, std::string name);
	virtual ~CGameObject() = 0 {};

	void SetID(GameObjectID value) { id = value; }
	GameObjectID GetID() { return id; }

	std::string GetName() { return name; }
	ActorType GetType() { return type; }

	void SetResourcePath(std::string resource_path) { this->resource_path = resource_path; }
	std::string GetResourcePath() { return resource_path; }

	void Destroy() { is_destroyed = true; }
	bool IsDestroyed() { return is_destroyed; }

	virtual void LoadFromFile(std::string file_path) = 0;
	virtual void Unload() = 0;
};
typedef CGameObject* pGameObject;

#endif // !__GAME_OBJECT_H__
