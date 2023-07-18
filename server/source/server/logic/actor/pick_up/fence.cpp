#include "server/logic/actor/pick_up/fence.h"
#include "server/play_scene.h"
#include "server/logic/record/pick_up/fence_record.h"

CFence::CFence(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::FENCE, name)
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

CFence::~CFence() {
}

void CFence::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CFence::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CFence::Unload() {
	ClearSprites();
}

void CFence::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CFence::Update(float elapsed_ms) {
}

void CFence::Render(sf::RenderWindow& window) {
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

void CFence::OnCollisionEnter(CBody* other) {
}

void CFence::OnCollisionExit(CBody* other) {
}

void CFence::HandleEvent(pEvent incomming_event) {
}

pRecord CFence::Serialize() {
	auto record = new CFenceRecord(GetRecordableID(), GetNetworkID());

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

void CFence::Deserialize(pRecord record) {
	auto fence_record = static_cast<pFenceRecord>(record);

	if (IsActive() != fence_record->is_active) {
		SetActive(fence_record->is_active);
	}

	if (IsVisible() != fence_record->is_visible) {
		SetVisible(fence_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != fence_record->is_enable) {
		GetPhysicsBody()->SetEnabled(fence_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != fence_record->is_awake) {
		GetPhysicsBody()->SetAwake(fence_record->is_awake);
	}

	if (IsSpawned() != fence_record->is_spawned) {
		SetSpawned(fence_record->is_spawned);
	}

	SetBodyPosition(fence_record->position_x, fence_record->position_y);
}

void CFence::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CFence::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
