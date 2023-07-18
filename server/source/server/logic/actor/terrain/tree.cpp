#include "server/logic/actor/terrain/tree.h"
#include "server/play_scene.h"

CTree::CTree(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::TREE, name)
	, CNetworkObject(play_scene)
	, CRenderable(play_scene)
	, CSprites(play_scene) {
	ObtainNetworkID();
}

CTree::~CTree() {
}

void CTree::Load(float position_x, float position_y, json& data) {
	SetPosition(position_x, position_y);
	LoadRenderableFromJson(data);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CTree::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CTree::Unload() {
	ClearSprites();
}

void CTree::PackLoadPacket(pPacket packet) {
	float x;
	float y;
	GetPosition(x, y);
	*packet << x << y;

	PackRenderableLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CTree::Render(sf::RenderWindow& window) {
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