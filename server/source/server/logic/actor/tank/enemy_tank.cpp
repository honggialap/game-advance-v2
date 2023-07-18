#include "server/logic/actor/tank/enemy_tank.h"
#include "server/logic/actor/tank/enemy_tank_spawner.h"
#include "server/play_scene.h"
#include "server/logic/record/tank/enemy_tank_record.h"

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
	auto record = new CEnemyTankRecord(GetRecordableID(), GetNetworkID());

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

void CEnemyTank::Deserialize(pRecord record) {
	auto enemy_tank_record = static_cast<pEnemyTankRecord>(record);

	if (IsActive() != enemy_tank_record->is_active) {
		SetActive(enemy_tank_record->is_active);
	}

	if (IsVisible() != enemy_tank_record->is_visible) {
		SetVisible(enemy_tank_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != enemy_tank_record->is_enable) {
		GetPhysicsBody()->SetEnabled(enemy_tank_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != enemy_tank_record->is_awake) {
		GetPhysicsBody()->SetAwake(enemy_tank_record->is_awake);
	}

	if (IsSpawned() != enemy_tank_record->is_spawned) {
		SetSpawned(enemy_tank_record->is_spawned);
	}

	SetBodyPosition(enemy_tank_record->position_x, enemy_tank_record->position_y);
	SetBodyVelocity(enemy_tank_record->velocity_x, enemy_tank_record->velocity_y);

	normal_x = enemy_tank_record->normal_x;
	normal_y = enemy_tank_record->normal_y;

	movement_x = enemy_tank_record->movement_x;
	movement_y = enemy_tank_record->movement_y;
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
