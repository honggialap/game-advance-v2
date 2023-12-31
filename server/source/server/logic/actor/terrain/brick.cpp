#include "server/logic/actor/terrain/brick.h"
#include "server/logic/actor/terrain/fence_spawner.h"
#include "server/play_scene.h"
#include "server/logic/record/terrain/brick_record.h"

CBrick::CBrick(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::BRICK, name)
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

CBrick::~CBrick() {
}

void CBrick::SetFenceSpawner(CFenceSpawner* spawner) {
	fence_spawner = spawner;
	fence_spawner->AddBrick(this);
}

void CBrick::Spawn() {
	is_spawned = true;
	SetActive(true);
	SetVisible(true);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CBrick::Despawn(){
	is_spawned = false;
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}

void CBrick::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CBrick::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CBrick::Unload() {
	ClearSprites();
}

void CBrick::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CBrick::Update(float elapsed_ms) {
}

void CBrick::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetBodyPosition(render_x, render_y);

	auto sprite = GetSprite(10);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CBrick::OnCollisionEnter(CBody* other) {
}

void CBrick::OnCollisionExit(CBody* other) {
}

void CBrick::HandleEvent(pEvent incomming_event) {
}

pRecord CBrick::Serialize() {
	auto record = new CBrickRecord(GetRecordableID(), GetNetworkID());

	record->is_active = IsActive();
	record->is_visible = IsVisible();

	record->is_enable = GetPhysicsBody()->IsEnabled();
	record->is_awake = GetPhysicsBody()->IsAwake();

	return record;
}

void CBrick::Deserialize(pRecord record) {
	auto brick_record = static_cast<pBrickRecord>(record);

	if (IsActive() != brick_record->is_active) {
		SetActive(brick_record->is_active);
	}

	if (IsVisible() != brick_record->is_visible) {
		SetVisible(brick_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != brick_record->is_enable) {
		GetPhysicsBody()->SetEnabled(brick_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != brick_record->is_awake) {
		GetPhysicsBody()->SetAwake(brick_record->is_awake);
	}
}


