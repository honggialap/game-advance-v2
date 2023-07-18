#include "client/logic/actor/tank/player_bullet.h"
#include "client/logic/actor/tank/player_tank.h"
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

	NetworkID network_id;
	*packet >> network_id;

	auto network_object = GetPlayScene().GetNetworkObject(network_id);
	auto player_tank = dynamic_cast<pPlayerTank>(network_object);
	SetTank(player_tank);
}

void CPlayerBullet::HandleStatePacket(pPacket packet) {
	bool is_active;
	*packet >> is_active;
	if (IsActive() != is_active) {
		SetActive(is_active);
	}

	bool is_visible;
	*packet >> is_visible;
	if (IsVisible() != is_visible) {
		SetVisible(is_visible);
	}

	bool is_enable = false;
	*packet >> is_enable;
	if (GetPhysicsBody()->IsEnabled() != is_enable) {
		GetPhysicsBody()->SetEnabled(is_enable);
	}

	bool is_awake = false;
	*packet >> is_awake;
	if (GetPhysicsBody()->IsAwake() != is_awake) {
		GetPhysicsBody()->SetAwake(is_awake);
	}

	bool is_shot = false;
	*packet >> is_shot;
	if (IsShot() != is_shot) {
		SetShot(is_shot);
	}

	float position_x = 0.0f;
	float position_y = 0.0f;
	*packet >> position_x >> position_y;
	SetBodyPosition(position_x, position_y);
	SetLatestPosition(position_x, position_y);

	float velocity_x = 0.0f;
	float velocity_y = 0.0f;
	*packet >> velocity_x >> velocity_y;
	SetBodyVelocity(velocity_x, velocity_y);

	int8_t normal_x = 0;
	int8_t normal_y = 0;
	*packet >> normal_x >> normal_y;
	this->normal_x = normal_x;
	this->normal_y = normal_y;
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
		float latest_tick = (float)GetPlayScene().GetLatestTick();
		float reconcilate_tick = (float)GetPlayScene().GetReconcileTick();
		float tick_per_game_state = (float)GetPlayScene().GetTickPerGameState();
		float interpolate = (latest_tick - reconcilate_tick - tick_per_game_state) / tick_per_game_state;
		GetInterpolated(render_x, render_y, interpolate);
	}

	SpriteID sprite_id = 1;
	if (normal_x != 0) {
		if (normal_x == 1) sprite_id = 4;
		else sprite_id = 2;
	}
	else {
		if (normal_y == 1) sprite_id = 1;
		else sprite_id = 3;
	}

	auto sprite = GetSprite(sprite_id);
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

void CPlayerBullet::OnShoot(float x, float y, int8_t normal_x, int8_t normal_y) {
	SetActive(true);
	SetVisible(true);
	GetPhysicsBody()->SetEnabled(true);
	GetPhysicsBody()->SetAwake(true);
	SetBodyPosition(x, y);
	SetBodyVelocity(speed * normal_x, speed * normal_y);
	this->normal_x = normal_x;
	this->normal_y = normal_y;
}

void CPlayerBullet::OnImpact() {
	SetActive(false);
	SetVisible(false);
	GetPhysicsBody()->SetEnabled(false);
	GetPhysicsBody()->SetAwake(false);
}
