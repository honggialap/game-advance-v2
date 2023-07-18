#include "client/logic/actor/tank/enemy_tank.h"
#include "client/play_scene.h"

CEnemyTank::CEnemyTank(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::ENEMY_TANK, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene)
	, CRenderable(play_scene)
	, CSprites(play_scene) {
}

CEnemyTank::~CEnemyTank() {
}

void CEnemyTank::LoadFromFile(std::string file_path) {
	std::ifstream data_file(file_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	LoadSpritesFromJson(data);
}

void CEnemyTank::Unload() {
	ClearSprites();
}

void CEnemyTank::LoadFromPacket(pPacket packet) {
	LoadRenderableFromPacket(packet);
	LoadBodyFromPacket(packet);

	std::string resource_path;
	*packet >> resource_path;
	SetResourcePath(resource_path);
	LoadFromFile(resource_path);
}

void CEnemyTank::HandleStatePacket(pPacket packet) {
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

void CEnemyTank::Render(sf::RenderWindow& window) {
	float render_x;
	float render_y;

	float latest_tick = GetPlayScene().GetLatestTick();
	float reconcilate_tick = GetPlayScene().GetReconcileTick();
	float tick_per_game_state = GetPlayScene().GetTickPerGameState();
	float interpolate = (latest_tick - reconcilate_tick - tick_per_game_state) / tick_per_game_state;
	GetInterpolated(render_x, render_y, interpolate);

	SpriteID sprite_id = 11;
	if (normal_x != 0) {
		if (normal_x == 1) sprite_id = 14;
		else sprite_id = 12;
	}
	else {
		if (normal_y == 1) sprite_id = 11;
		else sprite_id = 13;
	}

	auto sprite = GetSprite(sprite_id);
	sprite->setPosition(
		render_x,
		-render_y + window.getSize().y
	);
	window.draw(*sprite);
}

void CEnemyTank::OnCollisionEnter(CBody* other) {
}

void CEnemyTank::OnCollisionExit(CBody* other) {
}
