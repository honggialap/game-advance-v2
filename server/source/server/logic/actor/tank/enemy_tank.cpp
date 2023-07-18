#include "server/logic/actor/tank/enemy_tank.h"
#include "server/logic/actor/tank/enemy_tank_spawner.h"
#include "server/play_scene.h"

CEnemyTank::CEnemyTank(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::ENEMY_TANK, name)
	, CNetworkObject(play_scene)
	, CInputHandler(play_scene)
	, CCommandable(play_scene, GetID())
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

CEnemyTank::~CEnemyTank() {
}

void CEnemyTank::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);

	speed = data.at("speed");
}

void CEnemyTank::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CEnemyTank::Unload() {
	ClearSprites();
}

void CEnemyTank::PackLoadPacket(pPacket packet) {
	PackUpdatableLoadPacket(packet);
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CEnemyTank::HandleInput(Tick tick) {
}

void CEnemyTank::ExecuteCommand(pCommand command) {
}

void CEnemyTank::Update(float elapsed_ms) {
}

void CEnemyTank::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetBodyPosition(render_x, render_y);

	auto sprite = GetSprite(11);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CEnemyTank::OnCollisionEnter(CBody* other) {
}

void CEnemyTank::OnCollisionExit(CBody* other) {
}

void CEnemyTank::HandleEvent(pEvent incomming_event) {
	Despawn();
}

pRecord CEnemyTank::Serialize() {
	return pRecord();
}

void CEnemyTank::Deserialize(pRecord record) {
}

void CEnemyTank::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CEnemyTank::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
