#include "server/logic/actor/tank/player_tank.h"
#include "server/logic/actor/tank/player_tank_spawner.h"
#include "server/play_scene.h"
#include "server/logic/record/tank/player_tank_record.h"

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
	auto record = new CPlayerTankRecord(GetRecordableID(), GetNetworkID());

	record->is_active = IsActive();
	record->is_visible = IsVisible();

	record->is_enable = GetPhysicsBody()->IsEnabled();
	record->is_awake = GetPhysicsBody()->IsAwake();

	record->is_spawned = IsSpawned();

	float position_x;
	float position_y;
	GetBodyPosition(position_x, position_y);
	record->position_x = position_x;
	record->position_y = position_y;

	float velocity_x;
	float velocity_y;
	GetBodyVelocity(velocity_x, velocity_y);
	record->velocity_x = velocity_x;
	record->velocity_y = velocity_y;

	record->normal_x = normal_x;
	record->normal_y = normal_y;

	record->movement_x = movement_x;
	record->movement_y = movement_y;

	return record;
}

void CPlayerTank::Deserialize(pRecord record) {
	auto player_tank_record = static_cast<pPlayerTankRecord>(record);

	if (IsActive() != player_tank_record->is_active) {
		SetActive(player_tank_record->is_active);
	}

	if (IsVisible() != player_tank_record->is_visible) {
		SetVisible(player_tank_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != player_tank_record->is_enable) {
		GetPhysicsBody()->SetEnabled(player_tank_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != player_tank_record->is_awake) {
		GetPhysicsBody()->SetAwake(player_tank_record->is_awake);
	}

	if (IsSpawned() != player_tank_record->is_spawned) {
		SetSpawned(player_tank_record->is_spawned);
	}

	SetBodyPosition(player_tank_record->position_x, player_tank_record->position_y);
	SetBodyVelocity(player_tank_record->velocity_x, player_tank_record->velocity_y);

	normal_x = player_tank_record->normal_x;
	normal_y = player_tank_record->normal_y;

	movement_x = player_tank_record->movement_x;
	movement_y = player_tank_record->movement_y;
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
