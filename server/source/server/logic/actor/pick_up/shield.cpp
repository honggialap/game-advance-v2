#include "server/logic/actor/pick_up/shield.h"
#include "server/play_scene.h"
#include "server/logic/record/pick_up/shield_record.h"

CShield::CShield(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::SHIELD, name)
	, CNetworkObject(play_scene)
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRecordable(play_scene, GetID())
	, CRenderable(play_scene)
	, CSprites(play_scene) {
	ObtainNetworkID();
	//SubcribeEvent(EEventType::INVALID_EVENT);
}

CShield::~CShield() {
}

void CShield::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CShield::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CShield::Unload() {
	ClearSprites();
}

void CShield::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CShield::Update(float elapsed_ms) {
}

void CShield::Render(sf::RenderWindow& window) {
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

void CShield::OnCollisionEnter(CBody* other) {
}

void CShield::OnCollisionExit(CBody* other) {
}

void CShield::HandleEvent(pEvent incomming_event) {
}

pRecord CShield::Serialize() {
	auto record = new CShieldRecord(GetRecordableID(), GetNetworkID());

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

void CShield::Deserialize(pRecord record) {
	auto shield_record = static_cast<pShieldRecord>(record);

	if (IsActive() != shield_record->is_active) {
		SetActive(shield_record->is_active);
	}

	if (IsVisible() != shield_record->is_visible) {
		SetVisible(shield_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != shield_record->is_enable) {
		GetPhysicsBody()->SetEnabled(shield_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != shield_record->is_awake) {
		GetPhysicsBody()->SetAwake(shield_record->is_awake);
	}

	if (IsSpawned() != shield_record->is_spawned) {
		SetSpawned(shield_record->is_spawned);
	}

	SetBodyPosition(shield_record->position_x, shield_record->position_y);
}

void CShield::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x,y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CShield::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
