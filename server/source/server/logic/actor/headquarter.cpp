#include "server/logic/actor/headquarter.h"
#include "server/play_scene.h"
#include "server/logic/record/headquarter_record.h"

CHeadquarter::CHeadquarter(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::HEADQUARTER, name)
	, CNetworkObject(play_scene)
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRecordable(play_scene, GetID())
	, CRenderable(play_scene)
	, CSprites(play_scene) {
	ObtainNetworkID();
}

CHeadquarter::~CHeadquarter() {
}

void CHeadquarter::Load(float position_x, float position_y, json& data) {
	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadBodyFromJson(data, position_x, position_y);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CHeadquarter::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CHeadquarter::Unload() {
	ClearSprites();
}

void CHeadquarter::PackLoadPacket(pPacket packet) {
	PackRenderableLoadPacket(packet);
	PackBodyLoadPacket(packet);
	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CHeadquarter::Update(float elapsed_ms) {
}

void CHeadquarter::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetBodyPosition(render_x, render_y);

	SceneID sprite_id;
	switch (state) {
	case HQ_IDLE: sprite_id = 1; break;
	case HQ_DESTROYED: sprite_id = 2; break;
	default: sprite_id = 1; break;
	}

	auto sprite = GetSprite(sprite_id);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CHeadquarter::OnCollisionEnter(CBody* other) {
}

void CHeadquarter::OnCollisionExit(CBody* other) {
}

void CHeadquarter::HandleEvent(pEvent incomming_event) {
}

pRecord CHeadquarter::Serialize() {
	auto record = new CHeadquarterRecord(GetRecordableID(), GetNetworkID());

	record->is_active = IsActive();
	record->is_visible = IsVisible();

	record->is_enable = GetPhysicsBody()->IsEnabled();
	record->is_awake = GetPhysicsBody()->IsAwake();

	record->state = GetState();

	return record;
}

void CHeadquarter::Deserialize(pRecord record) {
	auto headquarter_record = static_cast<pHeadquarterRecord>(record);

	if (IsActive() != headquarter_record->is_active) {
		SetActive(headquarter_record->is_active);
	}

	if (IsVisible() != headquarter_record->is_visible) {
		SetVisible(headquarter_record->is_visible);
	}

	if (GetPhysicsBody()->IsEnabled() != headquarter_record->is_enable) {
		GetPhysicsBody()->SetEnabled(headquarter_record->is_enable);
	}

	if (GetPhysicsBody()->IsAwake() != headquarter_record->is_awake) {
		GetPhysicsBody()->SetAwake(headquarter_record->is_awake);
	}

	SetState(headquarter_record->state);
}
