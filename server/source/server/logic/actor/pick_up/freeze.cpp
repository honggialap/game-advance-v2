#include "server/logic/actor/pick_up/freeze.h"
#include "server/play_scene.h"
#include "server/logic/record/pick_up/freeze_record.h"

CFreeze::CFreeze(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::FREEZE, name)
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

CFreeze::~CFreeze() {
}

void CFreeze::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CFreeze::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CFreeze::Unload() {
	ClearSprites();
}

void CFreeze::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CFreeze::Update(float elapsed_ms) {
}

void CFreeze::Render(sf::RenderWindow& window) {
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

void CFreeze::OnCollisionEnter(CBody* other) {
}

void CFreeze::OnCollisionExit(CBody* other) {
}

void CFreeze::HandleEvent(pEvent incomming_event) {
}

pRecord CFreeze::Serialize() {
	auto record = new CFreezeRecord(GetRecordableID(), GetNetworkID());

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

void CFreeze::Deserialize(pRecord record) {
	auto freeze_record = static_cast<pFreezeRecord>(record);

	if (IsActive() != freeze_record->is_active) {
		SetActive(freeze_record->is_active);
	}

	if (IsVisible() != freeze_record->is_visible) {
		SetVisible(freeze_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != freeze_record->is_enable) {
		GetPhysicsBody()->SetEnabled(freeze_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != freeze_record->is_awake) {
		GetPhysicsBody()->SetAwake(freeze_record->is_awake);
	}

	if (IsSpawned() != freeze_record->is_spawned) {
		SetSpawned(freeze_record->is_spawned);
	}

	SetBodyPosition(freeze_record->position_x, freeze_record->position_y);
}

void CFreeze::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CFreeze::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
