#include "server/logic/actor/pick_up/bomb.h"
#include "server/play_scene.h"
#include "server/logic/record/pick_up/bomb_record.h"

CBomb::CBomb(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::BOMB, name)
	, CNetworkObject(play_scene)
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRecordable(play_scene, GetID())
	, CRenderable(play_scene)
	, CSprites(play_scene)
{
	ObtainNetworkID();
	//SubcribeEvent(EEventType::INVALID_EVENT);
}

CBomb::~CBomb() {
}

void CBomb::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CBomb::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CBomb::Unload() {
	ClearSprites();
}

void CBomb::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CBomb::Update(float elapsed_ms) {
}

void CBomb::Render(sf::RenderWindow& window) {
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

void CBomb::OnCollisionEnter(CBody* other) {
}

void CBomb::OnCollisionExit(CBody* other) {
}

void CBomb::HandleEvent(pEvent incomming_event) {
}

pRecord CBomb::Serialize() {
	auto record = new CBombRecord(GetRecordableID(), GetNetworkID());

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

	return record;
}

void CBomb::Deserialize(pRecord record) {
	auto bomb_record = static_cast<pBombRecord>(record);

	if (IsActive() != bomb_record->is_active) {
		SetActive(bomb_record->is_active);
	}

	if (IsVisible() != bomb_record->is_visible) {
		SetVisible(bomb_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != bomb_record->is_enable) {
		GetPhysicsBody()->SetEnabled(bomb_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != bomb_record->is_awake) {
		GetPhysicsBody()->SetAwake(bomb_record->is_awake);
	}

	if (IsSpawned() != bomb_record->is_spawned) {
		SetSpawned(bomb_record->is_spawned);
	}

	SetBodyPosition(bomb_record->position_x, bomb_record->position_y);
}

void CBomb::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CBomb::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
