#include "server/logic/actor/tank/player_tank.h"
#include "server/logic/actor/tank/player_tank_spawner.h"
#include "server/play_scene.h"

CPlayerTank::CPlayerTank(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::PLAYER_TANK, name)
	, CNetworkObject(play_scene)
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

CPlayerTank::~CPlayerTank() {
}

void CPlayerTank::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);

	PlayerID player = data.at("player");
	SetPlayerID(player);
	
	speed = data.at("speed");
}

void CPlayerTank::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CPlayerTank::Unload() {
	ClearSprites();
}

void CPlayerTank::PackLoadPacket(pPacket packet) {
	PackUpdatableLoadPacket(packet);
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;

	PlayerID player_id = GetPlayerID();
	*packet << player_id;

	float speed = this->speed;
	*packet << speed;
}

void CPlayerTank::ExecuteCommand(pCommand command) {
}

void CPlayerTank::Update(float elapsed_ms) {
}

void CPlayerTank::Render(sf::RenderWindow& window) {
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

void CPlayerTank::OnCollisionEnter(CBody* other) {
}

void CPlayerTank::OnCollisionExit(CBody* other) {
}

void CPlayerTank::HandleEvent(pEvent incomming_event) {
	Despawn();
}

pRecord CPlayerTank::Serialize() {
	return pRecord();
}

void CPlayerTank::Deserialize(pRecord record) {
}

void CPlayerTank::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CPlayerTank::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
