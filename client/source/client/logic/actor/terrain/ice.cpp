#include "client/logic/actor/terrain/ice.h"
#include "client/play_scene.h"

CIce::CIce(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::ICE, name)
	, CNetworkObject(play_scene)
	, CRenderable(play_scene) 
	, CSprites(play_scene) {
}

CIce::~CIce() {
}

void CIce::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CIce::Unload() {
	ClearSprites();
}

void CIce::LoadFromPacket(pPacket packet) {
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

void CIce::HandleStatePacket(pPacket packet) {
}

void CIce::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetPosition(render_x, render_y);

	auto sprite = GetSprite(1);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}
