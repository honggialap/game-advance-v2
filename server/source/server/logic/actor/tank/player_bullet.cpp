#include "server/logic/actor/tank/player_bullet.h"
#include "server/logic/actor/tank/player_tank.h"
#include "server/play_scene.h"
#include "server/logic/record/tank/player_bullet_record.h"

CPlayerBullet::CPlayerBullet(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::PLAYER_BULLET, name)
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

CPlayerBullet::~CPlayerBullet() {
}

void CPlayerBullet::Load(float position_x, float position_y, json& data) {
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

void CPlayerBullet::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CPlayerBullet::Unload() {
	ClearSprites();
}

void CPlayerBullet::PackLoadPacket(pPacket packet) {
	PackUpdatableLoadPacket(packet);
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;

	PlayerID player_id = GetPlayerID();
	*packet << player_id;

	float speed = this->speed;
	*packet << speed;

	auto player_tank = static_cast<pPlayerTank>(GetTank());
	auto network_object = dynamic_cast<pNetworkObject>(player_tank);
	NetworkID network_id = network_object->GetNetworkID();
	*packet << network_id;
}

void CPlayerBullet::Update(float elapsed_ms) {
}

void CPlayerBullet::Render(sf::RenderWindow& window) {
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

void CPlayerBullet::OnCollisionEnter(CBody* other) {
}

void CPlayerBullet::OnCollisionExit(CBody* other) {
}

void CPlayerBullet::HandleEvent(pEvent incomming_event) {
	Impact();
}

pRecord CPlayerBullet::Serialize() {
	auto record = new CPlayerBulletRecord(GetRecordableID(), GetNetworkID());

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

void CPlayerBullet::Deserialize(pRecord record) {
	auto player_bullet_record = static_cast<pPlayerBulletRecord>(record);

	if (IsActive() != player_bullet_record->is_active) {
		SetActive(player_bullet_record->is_active);
	}

	if (IsVisible() != player_bullet_record->is_visible) {
		SetVisible(player_bullet_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != player_bullet_record->is_enable) {
		GetPhysicsBody()->SetEnabled(player_bullet_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != player_bullet_record->is_awake) {
		GetPhysicsBody()->SetAwake(player_bullet_record->is_awake);
	}

	if (IsShot() != player_bullet_record->is_shot) {
		SetShot(player_bullet_record->is_shot);
	}

	SetBodyPosition(player_bullet_record->position_x, player_bullet_record->position_y);
	SetBodyVelocity(player_bullet_record->velocity_x, player_bullet_record->velocity_y);

	normal_x = player_bullet_record->normal_x;
	normal_y = player_bullet_record->normal_y;
}

void CPlayerBullet::OnShoot(float x, float y, int8_t nx, int8_t ny) {
	SetActive(true);
	SetVisible(true);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
	SetBodyPosition(x, y);
	SetBodyVelocity(speed * nx, speed * ny);
	normal_x = nx;
	normal_y = ny;
}

void CPlayerBullet::OnImpact() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}

