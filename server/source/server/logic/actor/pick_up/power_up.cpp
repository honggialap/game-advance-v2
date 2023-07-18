#include "server/logic/actor/pick_up/power_up.h"
#include "server/play_scene.h"
#include "server/logic/record/pick_up/power_up_record.h"

CPowerUp::CPowerUp(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::POWER_UP, name)
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

CPowerUp::~CPowerUp() {
}

void CPowerUp::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CPowerUp::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CPowerUp::Unload() {
	ClearSprites();
}

void CPowerUp::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CPowerUp::Update(float elapsed_ms) {
}

void CPowerUp::Render(sf::RenderWindow& window) {
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

void CPowerUp::OnCollisionEnter(CBody* other) {
}

void CPowerUp::OnCollisionExit(CBody* other) {
}

void CPowerUp::HandleEvent(pEvent incomming_event) {
}

pRecord CPowerUp::Serialize() {
	auto record = new CPowerUpRecord(GetRecordableID(), GetNetworkID());

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

void CPowerUp::Deserialize(pRecord record) {
	auto power_up_record = static_cast<pPowerUpRecord>(record);

	if (IsActive() != power_up_record->is_active) {
		SetActive(power_up_record->is_active);
	}

	if (IsVisible() != power_up_record->is_visible) {
		SetVisible(power_up_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != power_up_record->is_enable) {
		GetPhysicsBody()->SetEnabled(power_up_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != power_up_record->is_awake) {
		GetPhysicsBody()->SetAwake(power_up_record->is_awake);
	}

	if (IsSpawned() != power_up_record->is_spawned) {
		SetSpawned(power_up_record->is_spawned);
	}

	SetBodyPosition(power_up_record->position_x, power_up_record->position_y);
}

void CPowerUp::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CPowerUp::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
