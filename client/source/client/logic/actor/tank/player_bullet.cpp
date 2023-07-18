#include "client/logic/actor/tank/player_bullet.h"
#include "client/play_scene.h"
#include "client/game_client.h"

CPlayerBullet::CPlayerBullet(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::PLAYER_BULLET, name)
	, CNetworkObject(play_scene)
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CSprites(play_scene)
	, CRenderable(play_scene) {
	SubcribeEvent(EEventType::INVALID_EVENT);
}

CPlayerBullet::~CPlayerBullet() {
}

void CPlayerBullet::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CPlayerBullet::Unload() {
	ClearSprites();
}

void CPlayerBullet::LoadFromPacket(pPacket packet) {
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

void CPlayerBullet::HandleStatePacket(pPacket packet) {
}

void CPlayerBullet::Update(float elapsed_ms) {
}

void CPlayerBullet::Render(sf::RenderWindow& window) {
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

void CPlayerBullet::OnCollisionEnter(CBody* other) {
}

void CPlayerBullet::OnCollisionExit(CBody* other) {
}

void CPlayerBullet::HandleEvent(pEvent incomming_event) {
}

void CPlayerBullet::OnShoot(float x, float y, bool left, bool up)
{
}

void CPlayerBullet::OnImpact()
{
}
