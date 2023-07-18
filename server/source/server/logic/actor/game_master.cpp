#include "server/logic/actor/game_master.h"
#include "server/logic/record/game_master_record.h"
#include "server/play_scene.h"

CGameMaster::CGameMaster(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::GAME_MASTER, name)
	, CNetworkObject(play_scene)
	, CUpdatable(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRecordable(play_scene, GetID())
	, CRenderable(play_scene)
	, CSprites(play_scene) {
	//SubcribeEvent(EEventType::INVALID_EVENT);
	ObtainNetworkID();
}

CGameMaster::~CGameMaster() {
}

void CGameMaster::ChangeState(EGameMasterState new_state) {
	state = new_state;
	switch (new_state) {
	case GM_RUN: {
		SpawnPlayerTank(1);
		SpawnPlayerTank(2);
		break;
	}

	case GM_DONE: {

		break;
	}

	case GM_SET_UP:
	default: break;
	}
}

void CGameMaster::Load(float position_x, float position_y, json& data) {
	SetPosition(position_x, position_y);

	LoadUpdatableFromJson(data);
	LoadRenderableFromJson(data);
	LoadPlayerTankSpawner(data);
	LoadEnemyTankSpawner(data);
	LoadPickUpSpawner(data);

	std::string resource_path = data.at("resource_path");
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CGameMaster::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CGameMaster::Unload() {
	CPickUpSpawner::Clear();
	CPlayerTankSpawner::Clear();
	CEnemyTankSpawner::Clear();
}

void CGameMaster::PackLoadPacket(pPacket packet) {
	float x;
	float y;
	GetPosition(x, y);
	*packet << x << y;
	PackRenderableLoadPacket(packet);
	std::string resource_path = GetResourcePath();
	*packet << resource_path;
}

void CGameMaster::Update(float elapsed_ms) {
	switch (state) {
	case GM_SET_UP: {
		ChangeState(EGameMasterState::GM_RUN);
		break;
	}

	case GM_RUN: {
		if (spawn_interval_counter > 0.0f) {
			spawn_interval_counter -= elapsed_ms;
		}
		else {
			spawn_interval_counter = spawn_interval;
			SpawnEnemyTank();
			SpawnPlayerTank(1);
			SpawnPlayerTank(2);
		}
		break;
	}

	case GM_DONE:
	default: break;
	}
}

void CGameMaster::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;
	GetPosition(render_x, render_y);

	auto sprite = GetSprite(1);
	sprite->setPosition(render_x, render_y);
	window.draw(*sprite);
}

void CGameMaster::HandleEvent(pEvent incomming_event) {
}

pRecord CGameMaster::Serialize() {
	auto record = new CGameMasterRecord(GetRecordableID(), GetNetworkID());

	record->is_active = IsActive();
	record->is_visible = IsVisible();

	record->state = GetState();
	record->spawn_interval_coutner = spawn_interval_counter;

	return record;
}

void CGameMaster::Deserialize(pRecord record) {
	auto game_master_record = static_cast<pGameMasterRecord>(record);

	if (IsActive() != game_master_record->is_active) {
		SetActive(game_master_record->is_active);
	}

	if (IsVisible() != game_master_record->is_visible) {
		SetVisible(game_master_record->is_visible);
	}

	SetState(game_master_record->state);
	spawn_interval_counter = game_master_record->spawn_interval_coutner;
}
