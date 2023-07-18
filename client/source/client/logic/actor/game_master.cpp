#include "client/logic/actor/game_master.h"
#include "client/play_scene.h"

CGameMaster::CGameMaster(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::GAME_MASTER, name)
	, CNetworkObject(play_scene)
	, CRenderable(play_scene) 
	, CSprites(play_scene) {
}

CGameMaster::~CGameMaster() {
}

void CGameMaster::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CGameMaster::Unload() {
	ClearSprites();
}

void CGameMaster::LoadFromPacket(pPacket packet) {
	float x;
	float y;
	*packet >> x >> y;
	SetPosition(x, y);

	LoadRenderableFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CGameMaster::HandleStatePacket(pPacket packet) {
	// So sad, i got nothing to receive :(
}

void CGameMaster::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetPosition(render_x, render_y);

	auto sprite = GetSprite(1);
	sprite->setPosition(render_x, render_y);
	window.draw(*sprite);
}
