#include "client/logic/actor/terrain/brick.h"
#include "client/play_scene.h"

CBrick::CBrick(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::BRICK, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene)
	, CRenderable(play_scene)
	, CSprites(play_scene) {
}

CBrick::~CBrick() {
}

void CBrick::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CBrick::Unload() {
	ClearSprites();
}

void CBrick::LoadFromPacket(pPacket packet) {
	LoadRenderableFromPacket(packet);
	LoadBodyFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CBrick::HandleStatePacket(pPacket packet) {
}

void CBrick::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetBodyPosition(render_x, render_y);

	auto sprite = GetSprite(10);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CBrick::OnCollisionEnter(CBody* other) {
}

void CBrick::OnCollisionExit(CBody* other) {
}
