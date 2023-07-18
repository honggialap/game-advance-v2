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

	float position_x = 0.0f;
	float position_y = 0.0f;
	*packet >> position_x >> position_y;
	SetBodyPosition(position_x, position_y);
	SetLatestPosition(position_x, position_y);

	float velocity_x = 0.0f;
	float velocity_y = 0.0f;
	*packet >> velocity_x >> velocity_y;
	SetBodyVelocity(velocity_x, velocity_y);

	int8_t movement_x = 0;
	int8_t movement_y = 0;
	*packet >> movement_x >> movement_y;
	this->movement_x = movement_x;
	this->movement_y = movement_y;

	int8_t normal_x = 0;
	int8_t normal_y = 0;
	*packet >> normal_x >> normal_y;
	this->normal_x = normal_x;
	this->normal_y = normal_y;
}

void CPlayerTank::HandleInput(Tick tick) {
	if (!IsActive()) return;
	if (GetPlayScene().GetGameClient().GetPlayerID() != GetPlayerID()) return;
	if (!GetPlayScene().GetGameClient().GetGameWindow().hasFocus()) return;

	int8_t movement_x = 0;
	int8_t movement_y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		movement_y = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		movement_y = -1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movement_x = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movement_x = -1;
	}

	if (this->movement_x != movement_x || this->movement_y != movement_y) {
		if (movement_x != 0) normal_x = movement_x;
		if (movement_y != 0) normal_y = movement_y;
		this->movement_x = movement_x;
		this->movement_y = movement_y;

		auto command = new CMoveCommand(GetCommandableID(), GetNetworkID(), movement_x, movement_y);
		GetPlayScene().AddCommandAtTick(tick, command);
		GetPlayScene().SendMovePacket(tick, command);
	}

	if (IsShootable()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			auto command = new CShootCommand(GetCommandableID(), GetNetworkID(), normal_x, normal_y);
			GetPlayScene().AddCommandAtTick(tick, command);
			GetPlayScene().SendShootPacket(tick, command);
		}
	}

}

void CPlayerTank::ExecuteCommand(pCommand command) {
	switch (command->type) {
	case ECommandType::MOVE: {
		auto move_command = static_cast<pMoveCommand>(command);
		SetBodyVelocity(
			speed * move_command->movement_x
			, speed * move_command->movement_y
		);
		break;
	}

	case ECommandType::SHOOT: {
		auto shoot_command = static_cast<pShootCommand>(command);
		float position_x;
		float position_y;
		GetBodyPosition(position_x, position_y);
		Shoot(position_x, position_y, shoot_command->normal_x, shoot_command->normal_y);
		break;
	}
	default: break;
	}
}

void CPlayerTank::Update(float elapsed_ms) {
	// i don't even know what to use in here :/
}

void CPlayerTank::Render(sf::RenderWindow& window) {
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

void CPlayerTank::OnCollisionEnter(CBody* other) {
}

void CPlayerTank::OnCollisionExit(CBody* other) {
}

void CPlayerTank::HandleEvent(pEvent incomming_event) {
}
