#include "client/logic/actor/pick_up/shield.h"
#include "client/play_scene.h"

CShield::CShield(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::SHIELD, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene)
	, CRenderable(play_scene)
	, CSprites(play_scene) {
}

CShield::~CShield() {
}

void CShield::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CShield::Unload() {
	ClearSprites();
}

void CShield::LoadFromPacket(pPacket packet) {
	LoadRenderableFromPacket(packet);
	LoadBodyFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CShield::HandleStatePacket(pPacket packet) {
}

void CShield::Render(sf::RenderWindow& window) {
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

void CShield::OnCollisionEnter(CBody* other) {
}

void CShield::OnCollisionExit(CBody* other) {
}
