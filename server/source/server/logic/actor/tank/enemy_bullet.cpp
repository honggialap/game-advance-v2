#include "server/logic/actor/tank/enemy_bullet.h"
#include "server/play_scene.h"

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
	PackUpdatableLoadPacket(packet);
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
	return pRecord();
}

void CEnemyBullet::Deserialize(pRecord record) {
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