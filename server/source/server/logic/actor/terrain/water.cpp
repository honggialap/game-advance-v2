#include "server/logic/actor/terrain/water.h"
#include "server/play_scene.h"

CWater::CWater(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::WATER, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene)
	, CRenderable(play_scene) 
	, CSprites(play_scene) {
	ObtainNetworkID();
}

CWater::~CWater() {
}

void CWater::Load(float position_x, float position_y, json& data) {
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CWater::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CWater::Unload() {
	ClearSprites();
}

void CWater::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CWater::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetBodyPosition(render_x, render_y);

	auto sprite = GetSprite(1);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CWater::OnCollisionEnter(CBody* other) {
}

void CWater::OnCollisionExit(CBody* other) {
}

