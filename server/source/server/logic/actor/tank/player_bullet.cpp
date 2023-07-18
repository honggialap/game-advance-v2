#include "server/logic/actor/tank/player_bullet.h"
#include "server/logic/actor/tank/player_tank.h"
#include "server/play_scene.h"

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
	return pRecord();
}

void CPlayerBullet::Deserialize(pRecord record) {
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

