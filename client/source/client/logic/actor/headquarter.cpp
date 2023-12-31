#include "client/logic/actor/headquarter.h"
#include "client/play_scene.h"

CHeadquarter::CHeadquarter(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::HEADQUARTER, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene)
	, CRenderable(play_scene)
	, CSprites(play_scene) {
}

CHeadquarter::~CHeadquarter() {
}

void CHeadquarter::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CHeadquarter::Unload() {
	ClearSprites();
}

void CHeadquarter::LoadFromPacket(pPacket packet) {
	LoadRenderableFromPacket(packet);
	LoadBodyFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CHeadquarter::HandleStatePacket(pPacket packet) {
	uint8_t state;
	*packet >> state;
	SetState(EHeadquarterState(state));
}

void CHeadquarter::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetBodyPosition(render_x, render_y);

	SpriteID sprite_id;
	switch (state) {
	case HQ_IDLE: sprite_id = 1; break;
	case HQ_DESTROYED: sprite_id = 2; break;
	default: sprite_id = 1; break;
	}

	auto sprite = GetSprite(sprite_id);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CHeadquarter::OnCollisionEnter(CBody* other) {
}

void CHeadquarter::OnCollisionExit(CBody* other) {
}
