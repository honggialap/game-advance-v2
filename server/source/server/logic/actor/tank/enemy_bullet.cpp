#include "server/logic/actor/tank/enemy_bullet.h"
#include "server/play_scene.h"
#include "server/logic/record/tank/enemy_bullet_record.h"

CEnemyBullet::CEnemyBullet(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::ENEMY_BULLET, name)
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

CEnemyBullet::~CEnemyBullet() {
}

void CEnemyBullet::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);

	speed = data.at("speed");
}

void CEnemyBullet::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CEnemyBullet::Unload() {
	ClearSprites();
}

void CEnemyBullet::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CEnemyBullet::Update(float elapsed_ms) {
}

void CEnemyBullet::Render(sf::RenderWindow& window) {
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

void CEnemyBullet::OnCollisionEnter(CBody* other) {
}

void CEnemyBullet::OnCollisionExit(CBody* other) {
}

void CEnemyBullet::HandleEvent(pEvent incomming_event) {
	Impact();
}

pRecord CEnemyBullet::Serialize() {
	auto record = new CEnemyBulletRecord(GetRecordableID(), GetNetworkID());

	record->is_active = IsActive();
	record->is_visible = IsVisible();

	record->is_enable = GetPhysicsBody()->IsEnabled();
	record->is_awake = GetPhysicsBody()->IsAwake();

	record->is_shot = IsShot();

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

	return record;
}

void CEnemyBullet::Deserialize(pRecord record) {
	auto enemy_bullet_record = static_cast<pEnemyBulletRecord>(record);

	if (IsActive() != enemy_bullet_record->is_active) {
		SetActive(enemy_bullet_record->is_active);
	}

	if (IsVisible() != enemy_bullet_record->is_visible) {
		SetVisible(enemy_bullet_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != enemy_bullet_record->is_enable) {
		GetPhysicsBody()->SetEnabled(enemy_bullet_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != enemy_bullet_record->is_awake) {
		GetPhysicsBody()->SetAwake(enemy_bullet_record->is_awake);
	}

	if (IsShot() != enemy_bullet_record->is_shot) {
		SetShot(enemy_bullet_record->is_shot);
	}

	SetBodyPosition(enemy_bullet_record->position_x, enemy_bullet_record->position_y);
	SetBodyVelocity(enemy_bullet_record->velocity_x, enemy_bullet_record->velocity_y);

	normal_x = enemy_bullet_record->normal_x;
	normal_y = enemy_bullet_record->normal_y;
}

void CEnemyBullet::OnShoot(float x, float y, int8_t nx, int8_t ny) {
	SetActive(true);
	SetVisible(true);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
	SetBodyPosition(x, y);
	SetBodyVelocity(speed * nx, speed * ny);
	normal_x = nx;
	normal_y = ny;
}

void CEnemyBullet::OnImpact() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}