#include "client/play_scene.h"
#include "client/game_client.h"
#include "client/logic/logic.h"

CPlayScene::CPlayScene(CGameClient& game_client)
	: game_client(game_client)
	, CClientScene(game_client)
	, CScene(game_client) {
}

CPlayScene::~CPlayScene() {
}

pGameObject CPlayScene::CreateGameObject(EActorType actor_type, std::string name) {
	switch (actor_type) {

	case GAME_MASTER:	return new CGameMaster(*this, name);
	case HEADQUARTER:	return new CHeadquarter(*this, name);

	case PLAYER_TANK:	return new CPlayerTank(*this, name);
	case PLAYER_BULLET:	return new CPlayerBullet(*this, name);
	case ENEMY_TANK:	return new CEnemyTank(*this, name);
	case ENEMY_BULLET:	return new CEnemyBullet(*this, name);

	case EXTRA_LIFE:	return new CExtraLife(*this, name);
	case POWER_UP:		return new CPowerUp(*this, name);
	case SHIELD:		return new CShield(*this, name);
	case BOMB:			return new CBomb(*this, name);
	case FREEZE:		return new CFreeze(*this, name);
	case FENCE:			return new CFence(*this, name);

	case BOUND:			return new CBound(*this, name);
	case BRICK:			return new CBrick(*this, name);
	case STEEL:			return new CSteel(*this, name);
	case TREE:			return new CTree(*this, name);
	case ICE:			return new CIce(*this, name);
	case WATER:			return new CWater(*this, name);

	case INVALID_ACTOR:
	default: return nullptr;
	}
}

void CPlayScene::Load(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	play_scene_id = SceneID(data.at("play_scene_id"));
	lobby_scene_id = SceneID(data.at("lobby_scene_id"));

	LoadTexturesFromJson(data);
}

void CPlayScene::Unload() {
	ClearGameObjects();
}

void CPlayScene::Update(float elapsed_ms) {
	switch (state) {
	case CPlayScene::EState::SYNC: {
		IncreaseSyncTick();
		break;
	}

	case CPlayScene::EState::RUN: {
		Tick latest_tick = CClientTickCounter::GetLatestTick();

		if (CClientTickCounter::IsReconcile()) {
			SetReconcile(false);
			Tick reconcilating_tick = CClientTickCounter::GetReconcileTick() + 1;
			for (reconcilating_tick; reconcilating_tick < latest_tick; reconcilating_tick++) {
				CCommandManager::ExecuteCommands(reconcilating_tick);
				CUpdateManager::Update(elapsed_ms);
				CWorld::UpdatePhysicsWorld(elapsed_ms);
				CEventManager::HandleEvent();
			}
		}
		
		CInputManager::HandleInput(latest_tick);
		CCommandManager::ExecuteCommands(latest_tick);
		CUpdateManager::Update(elapsed_ms);
		CWorld::UpdatePhysicsWorld(elapsed_ms);
		CEventManager::HandleEvent();

		Tick drop_tick = GetDropTick();
		CCommandManager::TrimCommands(drop_tick);

		CClientTickCounter::IncreaseLatestTick();

		break;
	}

	case CPlayScene::EState::LOADING:
	case CPlayScene::EState::DONE:
	default: break;
	}
}

void CPlayScene::Render(sf::RenderWindow& window) {
	CRenderManager::Render(window);
}

void CPlayScene::OnConnect() {
}

void CPlayScene::OnDisconnect() {
}

void CPlayScene::OnConnectFail() {
}

bool CPlayScene::ProcessPacket(std::shared_ptr<CPacket> packet) {
	switch (packet->GetPacketType()) {
	case HEAD_LOAD: {
		HandleHeadLoadPacket(packet.get());
		return true;
	}

	case BODY_LOAD: {
		HandleBodyLoadPacket(packet.get());
		return true;
	}

	case END_LOAD: {
		HandleEndLoadPacket(packet.get());
		return true;
	}

	case START_SYNC: {
		HandleStartSyncPacket(packet.get());
		return true;
	}

	case SYNC: {
		HandleSyncPacket(packet.get());
		return true;
	}

	case START_GAME: {
		HandleStartGamePacket(packet.get());
		return true;
	}

	case STATE: {
		HandleStatePacket(packet.get());
		return true;
	}

	case END_GAME: {
		HandleEndGamePacket(packet.get());
		return true;
	}

	default: return true;
	}
}



void CPlayScene::HandleHeadLoadPacket(pPacket packet) {
	Tick tick_per_game_state;
	*packet >> tick_per_game_state;
	SetTickPerGameState(tick_per_game_state);

	float gravity_x;
	float gravity_y;
	*packet >> gravity_x >> gravity_y;
	CreatePhysicsWorld(gravity_x, gravity_y);
}

void CPlayScene::HandleBodyLoadPacket(pPacket packet) {
	ActorType type;
	*packet >> type;

	std::string name;
	*packet >> name;

	NetworkID network_id;
	*packet >> network_id;

	auto game_object = CreateGameObject(EActorType(type), name);

	auto network_object = dynamic_cast<pNetworkObject>(game_object);
	network_object->AssignNetworkID(network_id);

	auto client_object = dynamic_cast<pClientObject>(game_object);
	client_object->LoadFromPacket(packet);
}

void CPlayScene::HandleEndLoadPacket(pPacket packet) {
	SendLoadDonePacket();
}

void CPlayScene::SendLoadDonePacket() {
	auto packet = std::make_shared<CPacket>(DONE_LOAD);

	PlayerID id = GetGameClient().GetPlayerID();
	*packet << id;

	GetGameClient().Send(packet);
}



void CPlayScene::HandleStartSyncPacket(pPacket packet) {
	SetState(EState::SYNC);
	SendSyncPacket();
}

void CPlayScene::SendSyncPacket() {
	auto packet = std::make_shared<CPacket>(SYNC);

	ClientID client_id = GetGameClient().GetClientId();
	*packet << client_id;

	Tick sync_tick = GetSyncTick();
	*packet << sync_tick;

	GetGameClient().Send(packet);
}

void CPlayScene::HandleSyncPacket(pPacket packet) {
	Tick reply_tick;
	*packet >> reply_tick;

	Tick latest_tick = (GetSyncTick() - reply_tick) / 2;
	SetLatestTick(latest_tick);
	//SetLatestTick(0);

	SendSyncDonePacket();
}

void CPlayScene::SendSyncDonePacket() {
	auto packet = std::make_shared<CPacket>(DONE_SYNC);

	PlayerID id = GetGameClient().GetPlayerID();
	*packet << id;

	GetGameClient().Send(packet);
}



void CPlayScene::HandleStartGamePacket(pPacket packet) {
	SetState(EState::RUN);
}

void CPlayScene::HandleStatePacket(pPacket packet) {
	Tick receive_tick;
	*packet >> receive_tick;

	if (receive_tick < GetDropTick()) return;

	SetReconcile(true);
	SetReconcileTick(receive_tick);

	GameObjectID record_count;
	*packet >> record_count;

	for (auto record = 0; record < record_count; record++) {
		NetworkID network_id;
		*packet >> network_id;

		auto network_object = GetNetworkObject(network_id);
		auto client_object = dynamic_cast<pClientObject>(network_object);
		client_object->HandleStatePacket(packet);
	}
}

void CPlayScene::HandleEndGamePacket(pPacket packet) {
	bool win;
	*packet >> win;

	if (win) {
		GetGameClient().PlayScene(play_scene_id);
	}
	else {
		GetGameClient().PlayScene(lobby_scene_id);
		GetGameClient().Disconnect();
	}
}



void CPlayScene::SendMovePacket(Tick tick, pMoveCommand command) {
	auto packet = std::make_shared<CPacket>(PLAYER_MOVE);
	Tick send_tick = tick;
	*packet << send_tick;

	NetworkID network_id = command->network_object_id;
	*packet << network_id;

	int8_t movement_x = command->movement_x;
	int8_t movement_y = command->movement_y;
	*packet << movement_x << movement_y;

	GetGameClient().Send(packet);
}

void CPlayScene::SendShootPacket(Tick tick, pShootCommand command) {
	auto packet = std::make_shared<CPacket>(PLAYER_SHOOT);
	Tick send_tick = tick;
	*packet << send_tick;

	NetworkID network_id = command->network_object_id;
	*packet << network_id;

	int8_t normal_x = command->normal_x;
	int8_t normal_y = command->normal_y;
	*packet << normal_x << normal_y;

	GetGameClient().Send(packet);
}
