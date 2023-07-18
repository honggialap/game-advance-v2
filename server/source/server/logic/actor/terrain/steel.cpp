#include "server/logic/actor/terrain/steel.h"
#include "server/logic/actor/terrain/fence_spawner.h"
#include "server/play_scene.h"

CSteel::CSteel(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::STEEL, name)
	, CNetworkObject(play_scene)
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRecordable(play_scene, GetID())
	, CRenderable(play_scene)
	, CSprites(play_scene) {
	SubcribeEvent(EEventType::INVALID_EVENT);
	ObtainNetworkID();
}

CSteel::~CSteel() {
}

void CSteel::SetFenceSpawner(CFenceSpawner* spawner) {
	fence_spawner = spawner;
	fence_spawner->AddSteel(this);
}

void CSteel::Spawn() {
	is_spawned = true;
	SetActive(true);
	SetVisible(true);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CSteel::Despawn() {
	is_spawned = false;
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}

void CSteel::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CSteel::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CSteel::Unload() {
	ClearSprites();
}

void CSteel::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CSteel::Update(float elapsed_ms) {
}

void CSteel::Render(sf::RenderWindow& window) {
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

void CSteel::OnCollisionEnter(CBody* other) {
}

void CSteel::OnCollisionExit(CBody* other) {
}

void CSteel::HandleEvent(pEvent incomming_event) {
}

pRecord CSteel::Serialize() {
	return pRecord();
}

void CSteel::Deserialize(pRecord record) {
}
