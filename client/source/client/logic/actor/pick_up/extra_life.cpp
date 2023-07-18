#include "client/logic/actor/pick_up/extra_life.h"
#include "client/play_scene.h"

CExtraLife::CExtraLife(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::EXTRA_LIFE, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene)
	, CRenderable(play_scene)
	, CSprites(play_scene) {
}

CExtraLife::~CExtraLife() {
}

void CExtraLife::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CExtraLife::Unload() {
	ClearSprites();
}

void CExtraLife::LoadFromPacket(pPacket packet) {
	LoadRenderableFromPacket(packet);
	LoadBodyFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CExtraLife::HandleStatePacket(pPacket packet) {
	bool is_visible;
	*packet >> is_visible;
	if (IsVisible() != is_visible) {
		SetVisible(is_visible);
	}

	bool is_enable;
	*packet >> is_enable;
	if (GetPhysicsBody()->IsEnabled() != is_enable) {
		GetPhysicsBody()->SetEnabled(is_enable);
	}

	bool is_awake;
	*packet >> is_awake;
	if (GetPhysicsBody()->IsAwake() != is_awake) {
		GetPhysicsBody()->SetAwake(is_awake);
	}

	float position_x;
	float position_y;
	*packet >> position_x >> position_y;
	SetBodyPosition(position_x, position_y);
}

void CExtraLife::Render(sf::RenderWindow& window) {
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

void CExtraLife::OnCollisionEnter(CBody* other) {
}

void CExtraLife::OnCollisionExit(CBody* other) {
}
