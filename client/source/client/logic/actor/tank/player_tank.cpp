#include "client/logic/actor/tank/player_tank.h"
#include "client/play_scene.h"
#include "client/game_client.h"

CPlayerTank::CPlayerTank(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::PLAYER_TANK, name)
	, CNetworkObject(play_scene)
	, CInputHandler(play_scene)
	, CCommandable(play_scene, GetID())
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CSprites(play_scene)
	, CRenderable(play_scene) {
	SubcribeEvent(EEventType::INVALID_EVENT);
}

CPlayerTank::~CPlayerTank() {
}

void CPlayerTank::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CPlayerTank::Unload() {
	ClearSprites();
}

void CPlayerTank::LoadFromPacket(pPacket packet) {
	LoadUpdatableFromPacket(packet);
	LoadRenderableFromPacket(packet);
	LoadBodyFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);

	PlayerID player_id;
	*packet >> player_id;
	SetPlayerID(player_id);
	if (player_id == GetPlayScene().GetGameClient().GetPlayerID()) {
		SetLocal(true);
	}

	float speed;
	*packet >> speed;
	this->speed = speed;
}

void CPlayerTank::HandleStatePacket(pPacket packet) {
}

void CPlayerTank::HandleInput(Tick tick) {
}

void CPlayerTank::ExecuteCommand(pCommand command) {
}

void CPlayerTank::Update(float elapsed_ms) {
}

void CPlayerTank::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;

	if (IsLocal()) {
		GetBodyPosition(render_x, render_y);
	}
	else {
		float latest_tick = GetPlayScene().GetLatestTick();
		float reconcilate_tick = GetPlayScene().GetReconcileTick();
		float tick_per_game_state = GetPlayScene().GetTickPerGameState();
		float interpolate = (latest_tick - reconcilate_tick - tick_per_game_state) / tick_per_game_state;
		GetInterpolated(render_x, render_y, interpolate);
	}

	auto sprite = GetSprite(11);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CPlayerTank::OnCollisionEnter(CBody* other) {
}

void CPlayerTank::OnCollisionExit(CBody* other) {
}

void CPlayerTank::HandleEvent(pEvent incomming_event) {
}
