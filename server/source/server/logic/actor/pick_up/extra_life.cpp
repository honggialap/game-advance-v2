#include "server/logic/actor/pick_up/extra_life.h"
#include "server/play_scene.h"
#include "server/logic/record/pick_up/extra_life_record.h"

CExtraLife::CExtraLife(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::EXTRA_LIFE, name)
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

CExtraLife::~CExtraLife() {
}

void CExtraLife::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CExtraLife::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CExtraLife::Unload() {
	ClearSprites();
}

void CExtraLife::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);

	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CExtraLife::Update(float elapsed_ms) {
}

void CExtraLife::Render(sf::RenderWindow& window) {
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

void CExtraLife::OnCollisionEnter(CBody* other) {
}

void CExtraLife::OnCollisionExit(CBody* other) {
}

void CExtraLife::HandleEvent(pEvent incomming_event) {
}

pRecord CExtraLife::Serialize() {
	auto record = new CExtraLifeRecord(GetRecordableID(), GetNetworkID());

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

void CExtraLife::Deserialize(pRecord record) {
	auto extra_life_record = static_cast<pExtraLifeRecord>(record);

	if (IsActive() != extra_life_record->is_active) {
		SetActive(extra_life_record->is_active);
	}

	if (IsVisible() != extra_life_record->is_visible) {
		SetVisible(extra_life_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != extra_life_record->is_enable) {
		GetPhysicsBody()->SetEnabled(extra_life_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != extra_life_record->is_awake) {
		GetPhysicsBody()->SetAwake(extra_life_record->is_awake);
	}

	if (IsSpawned() != extra_life_record->is_spawned) {
		SetSpawned(extra_life_record->is_spawned);
	}

	SetBodyPosition(extra_life_record->position_x, extra_life_record->position_y);
}

void CExtraLife::OnSpawn(float x, float y) {
	SetActive(true);
	SetVisible(true);
	SetBodyPosition(x, y);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
}

void CExtraLife::OnDespawn() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
