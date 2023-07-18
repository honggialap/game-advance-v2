#include "engine/framework/game_object/game_object_manager.h"

pGameObject CGameObjectManager::GetGameObject(GameObjectID id) {
	return game_objects[id];
}

pGameObject CGameObjectManager::GetGameObject(std::string name) {
	return game_objects[dictionary[name]];
}

void CGameObjectManager::AddGameObject(pGameObject game_object) {
	GameObjectID id = GetNextGameObjectID();
	game_object->SetID(id);
	game_objects[id] = game_object;
	dictionary[game_object->GetName()] = id;
}

void CGameObjectManager::CleanUpDestroyedGameObject() {
	for (auto iterator = game_objects.begin(); iterator != game_objects.end();) {
		auto game_object = (*iterator).second;

		if (!game_object->IsDestroyed()) {
			iterator++;
			continue;
		}

		std::string name = game_object->GetName();
		dictionary.erase(name);
		
		delete game_object;
		game_object = nullptr;

		game_objects.erase(iterator);
	}
}

void CGameObjectManager::ClearGameObjects() {
	for (auto& game_object_container : game_objects) {
		auto game_object = game_object_container.second;
		delete game_object; game_object = nullptr;
	}
	game_objects.clear();
	dictionary.clear();
}
