#include "engine/framework/game_object/game_object.h"
#include "engine/framework/game_object/game_object_manager.h"

CGameObject::CGameObject(CGameObjectManager& game_object_manager, ActorType type, std::string name)
	: game_object_manager(game_object_manager)
	, name(name)
	, type(type)
	, is_destroyed(false) {
	game_object_manager.AddGameObject(this);
}