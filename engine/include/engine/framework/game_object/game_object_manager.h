#pragma once
#ifndef __GAME_OBJECT_MANAGER_H__
#define __GAME_OBJECT_MANAGER_H__

#include "game_object.h"

class CGameObjectManager {
private:
	GameObjectID next_game_object_id = 0;
	std::map<GameObjectID, pGameObject> game_objects;
	std::unordered_map<std::string, GameObjectID> dictionary;

public:
	GameObjectID GetNextGameObjectID() { return next_game_object_id++; }
	size_t GetGameObjectCount() { return game_objects.size(); }

	std::map<GameObjectID, pGameObject>& GetAllGameObject() { return game_objects; }

	pGameObject GetGameObject(GameObjectID id);
	pGameObject GetGameObject(std::string name);

	void AddGameObject(pGameObject game_object);
	void CleanUpDestroyedGameObject();
	void ClearGameObjects();

	virtual pGameObject CreateGameObject(EActorType actorType, std::string name) = 0;
};
typedef CGameObjectManager* pGameObjectManager;

#endif // !__GAME_OBJECT_MANAGER_H__
