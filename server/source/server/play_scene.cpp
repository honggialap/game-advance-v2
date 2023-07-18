#include "server/play_scene.h"
#include "server/game_server.h"
#include "server/logic/logic.h"

CPlayScene::CPlayScene(CGameServer& game_server)
	: game_server(game_server)
	, CServerScene(game_server)
	, CScene(game_server) {
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

	next_play_scene_id = SceneID(data.at("next_play_scene_id"));
	lobby_scene_id = SceneID(data.at("lobby_scene_id"));
	count_down = float(data.at("count_down"));

	Tick tick_per_game_state = data.at("tick_per_game_state");
	SetTickPerGameState(tick_per_game_state);

	LoadTexturesFromJson(data);
	LoadWorldFromJson(data);

	// GAME_MASTER
	auto& game_master_data = data.at("game_master");
	std::string game_master_name = game_master_data.at("name");
	float game_master_pos_x = game_master_data.at("x");
	float game_master_pos_y = game_master_data.at("y");
	auto game_master = dynamic_cast<pGameMaster>(CreateGameObject(GAME_MASTER, game_master_name));
	game_master->Load(game_master_pos_x, game_master_pos_y, game_master_data);

	// PICK_UP
	{
		auto& bomb_data = data.at("bomb");
		std::string bomb_name = bomb_data.at("name");
		float bomb_pos_x = bomb_data.at("x");
		float bomb_pos_y = bomb_data.at("y");
		auto bomb = dynamic_cast<pBomb>(CreateGameObject(BOMB, bomb_name));
		bomb->Load(bomb_pos_x, bomb_pos_y, bomb_data);
		bomb->SetPickUpSpawner(game_master);
		bomb->Despawn();
	}
	{
		auto& extra_life_data = data.at("extra_life");
		std::string extra_life_name = extra_life_data.at("name");
		float extra_life_pos_x = extra_life_data.at("x");
		float extra_life_pos_y = extra_life_data.at("y");
		auto extra_life = dynamic_cast<pExtraLife>(CreateGameObject(EXTRA_LIFE, extra_life_name));
		extra_life->Load(extra_life_pos_x, extra_life_pos_y, extra_life_data);
		extra_life->SetPickUpSpawner(game_master);
		extra_life->Despawn();
	}
	{
		auto& power_up_data = data.at("power_up");
		std::string power_up_name = power_up_data.at("name");
		float power_up_pos_x = power_up_data.at("x");
		float power_up_pos_y = power_up_data.at("y");
		auto power_up = dynamic_cast<pPowerUp>(CreateGameObject(POWER_UP, power_up_name));
		power_up->Load(power_up_pos_x, power_up_pos_y, power_up_data);
		power_up->SetPickUpSpawner(game_master);
		power_up->Despawn();
	}
	{
		auto& fence_data = data.at("fence");
		std::string fence_name = fence_data.at("name");
		float fence_pos_x = fence_data.at("x");
		float fence_pos_y = fence_data.at("y");
		auto fence = dynamic_cast<pFence>(CreateGameObject(FENCE, fence_name));
		fence->Load(fence_pos_x, fence_pos_y, fence_data);
		fence->SetPickUpSpawner(game_master);
		fence->Despawn();
	}
	{
		auto& freeze_data = data.at("freeze");
		std::string freeze_name = freeze_data.at("name");
		float freeze_pos_x = freeze_data.at("x");
		float freeze_pos_y = freeze_data.at("y");
		auto freeze = dynamic_cast<pFreeze>(CreateGameObject(FREEZE, freeze_name));
		freeze->Load(freeze_pos_x, freeze_pos_y, freeze_data);
		freeze->SetPickUpSpawner(game_master);
		freeze->Despawn();
	}
	{
		auto& shield_data = data.at("shield");
		std::string shield_name = shield_data.at("name");
		float shield_pos_x = shield_data.at("x");
		float shield_pos_y = shield_data.at("y");
		auto shield = dynamic_cast<pShield>(CreateGameObject(SHIELD, shield_name));
		shield->Load(shield_pos_x, shield_pos_y, shield_data);
		shield->SetPickUpSpawner(game_master);
		shield->Despawn();
	}

	// PLAYER_1_TANK
	{
		auto& player_tank_1_data = data.at("player_tank_1");
		std::string player_tank_1_name = player_tank_1_data.at("name");
		float player_tank_1_pos_x = player_tank_1_data.at("x");
		float player_tank_1_pos_y = player_tank_1_data.at("y");
		auto player_tank_1 = dynamic_cast<pPlayerTank>(CreateGameObject(PLAYER_TANK, player_tank_1_name));
		player_tank_1->Load(player_tank_1_pos_x, player_tank_1_pos_y, player_tank_1_data);
		player_tank_1->SetPlayerTankSpawner(player_tank_1->GetPlayerID(), game_master);
		player_tank_1->Despawn();

		uint16_t player_tank_1_bullet_count = player_tank_1_data.at("bullet_count");
		auto& bullet_data = player_tank_1_data.at("bullet");
		std::string bullet_default_name = bullet_data.at("name");

		for (uint16_t bullet_counter = 1; bullet_counter <= player_tank_1_bullet_count; bullet_counter++) {
			std::stringstream bullet_name_stream;
			bullet_name_stream
				<< player_tank_1_name
				<< "_" << bullet_default_name
				<< "_" << bullet_counter;
			std::string bullet_name = bullet_name_stream.str();

			auto bullet = dynamic_cast<pPlayerBullet>(CreateGameObject(PLAYER_BULLET, bullet_name));
			bullet->Load(player_tank_1_pos_x, player_tank_1_pos_y, bullet_data);
			bullet->SetTank(player_tank_1);
			bullet->Impact();
		}
	}

	// PLAYER_2_TANK
	{
		auto& player_tank_2_data = data.at("player_tank_2");
		std::string player_tank_2_name = player_tank_2_data.at("name");
		float player_tank_2_pos_x = player_tank_2_data.at("x");
		float player_tank_2_pos_y = player_tank_2_data.at("y");
		auto player_tank_2 = dynamic_cast<pPlayerTank>(CreateGameObject(PLAYER_TANK, player_tank_2_name));
		player_tank_2->Load(player_tank_2_pos_x, player_tank_2_pos_y, player_tank_2_data);
		player_tank_2->SetPlayerTankSpawner(player_tank_2->GetPlayerID(), game_master);
		player_tank_2->Despawn();

		uint16_t player_tank_2_bullet_count = player_tank_2_data.at("bullet_count");
		auto& bullet_data = player_tank_2_data.at("bullet");
		std::string bullet_default_name = bullet_data.at("name");

		for (uint16_t bullet_counter = 2; bullet_counter <= player_tank_2_bullet_count; bullet_counter++) {
			std::stringstream bullet_name_stream;
			bullet_name_stream
				<< player_tank_2_name
				<< "_" << bullet_default_name
				<< "_" << bullet_counter;
			std::string bullet_name = bullet_name_stream.str();

			auto bullet = dynamic_cast<pPlayerBullet>(CreateGameObject(PLAYER_BULLET, bullet_name));
			bullet->Load(player_tank_2_pos_x, player_tank_2_pos_y, bullet_data);
			bullet->SetTank(player_tank_2);
			bullet->Impact();
		}
	}

	// ENEMY TANK
	auto& basic_default_data = data.at("basic_tank");
	auto& fast_default_data = data.at("fast_tank");
	auto& power_default_data = data.at("power_tank");
	auto& armor_default_data = data.at("armor_tank");

	std::vector<int16_t> waves;
	for (auto& wave : data.at("wave")) {
		waves.push_back(wave);
	}

	for (int16_t wave_counter = 0; wave_counter < waves.size(); wave_counter++) {
		int16_t enemy_type = waves[wave_counter];
		switch (enemy_type) {

		case 1: { // BASIC
			auto& enemy_tank_data = data.at("basic_tank");
			std::string enemy_tank_default_name = enemy_tank_data.at("name");

			std::stringstream enemy_tank_stream;
			enemy_tank_stream
				<< enemy_tank_default_name
				<< "_" << wave_counter;
			std::string enemy_tank_name = enemy_tank_stream.str();

			auto enemy_tank = dynamic_cast<pEnemyTank>(CreateGameObject(ENEMY_TANK, enemy_tank_name));
			enemy_tank->Load(0.0f, 0.0f, enemy_tank_data);
			enemy_tank->SetEnemyTankSpawner(game_master);
			enemy_tank->Despawn();

			uint16_t enemy_tank_bullet_count = enemy_tank_data.at("bullet_count");
			auto& bullet_data = enemy_tank_data.at("bullet");
			std::string bullet_default_name = bullet_data.at("name");

			for (uint16_t bullet_counter = 1; bullet_counter <= enemy_tank_bullet_count; bullet_counter++) {
				std::stringstream bullet_name_stream;
				bullet_name_stream
					<< enemy_tank_name
					<< "_" << bullet_default_name
					<< "_" << bullet_counter;
				std::string bullet_name = bullet_name_stream.str();

				auto bullet = dynamic_cast<pEnemyBullet>(CreateGameObject(ENEMY_BULLET, bullet_name));
				bullet->Load(0.0, 0.0, bullet_data);
				bullet->SetTank(enemy_tank);
				bullet->Impact();
			}
			break;
		}

		case 2: { // FAST
			auto& enemy_tank_data = data.at("fast_tank");
			std::string enemy_tank_default_name = enemy_tank_data.at("name");

			std::stringstream enemy_tank_stream;
			enemy_tank_stream
				<< enemy_tank_default_name
				<< "_" << wave_counter;
			std::string enemy_tank_name = enemy_tank_stream.str();

			auto enemy_tank = dynamic_cast<pEnemyTank>(CreateGameObject(ENEMY_TANK, enemy_tank_name));
			enemy_tank->Load(0.0f, 0.0f, enemy_tank_data);
			enemy_tank->SetEnemyTankSpawner(game_master);
			enemy_tank->Despawn();

			uint16_t enemy_tank_bullet_count = enemy_tank_data.at("bullet_count");
			auto& bullet_data = enemy_tank_data.at("bullet");
			std::string bullet_default_name = bullet_data.at("name");

			for (uint16_t bullet_counter = 1; bullet_counter <= enemy_tank_bullet_count; bullet_counter++) {
				std::stringstream bullet_name_stream;
				bullet_name_stream
					<< enemy_tank_name
					<< "_" << bullet_default_name
					<< "_" << bullet_counter;
				std::string bullet_name = bullet_name_stream.str();

				auto bullet = dynamic_cast<pEnemyBullet>(CreateGameObject(ENEMY_BULLET, bullet_name));
				bullet->Load(0.0, 0.0, bullet_data);
				bullet->SetTank(enemy_tank);
				bullet->Impact();
			}
			break;
		}

		case 3: { //POWER
			auto& enemy_tank_data = data.at("power_tank");
			std::string enemy_tank_default_name = enemy_tank_data.at("name");

			std::stringstream enemy_tank_stream;
			enemy_tank_stream
				<< enemy_tank_default_name
				<< "_" << wave_counter;
			std::string enemy_tank_name = enemy_tank_stream.str();

			auto enemy_tank = dynamic_cast<pEnemyTank>(CreateGameObject(ENEMY_TANK, enemy_tank_name));
			enemy_tank->Load(0.0f, 0.0f, enemy_tank_data);
			enemy_tank->SetEnemyTankSpawner(game_master);
			enemy_tank->Despawn();

			uint16_t enemy_tank_bullet_count = enemy_tank_data.at("bullet_count");
			auto& bullet_data = enemy_tank_data.at("bullet");
			std::string bullet_default_name = bullet_data.at("name");

			for (uint16_t bullet_counter = 1; bullet_counter <= enemy_tank_bullet_count; bullet_counter++) {
				std::stringstream bullet_name_stream;
				bullet_name_stream
					<< enemy_tank_name
					<< "_" << bullet_default_name
					<< "_" << bullet_counter;
				std::string bullet_name = bullet_name_stream.str();

				auto bullet = dynamic_cast<pEnemyBullet>(CreateGameObject(ENEMY_BULLET, bullet_name));
				bullet->Load(0.0, 0.0, bullet_data);
				bullet->SetTank(enemy_tank);
				bullet->Impact();
			}
			break;
		}

		case 4: { // ARMOR
			auto& enemy_tank_data = data.at("armor_tank");
			std::string enemy_tank_default_name = enemy_tank_data.at("name");

			std::stringstream enemy_tank_stream;
			enemy_tank_stream
				<< enemy_tank_default_name
				<< "_" << wave_counter;
			std::string enemy_tank_name = enemy_tank_stream.str();

			auto enemy_tank = dynamic_cast<pEnemyTank>(CreateGameObject(ENEMY_TANK, enemy_tank_name));
			enemy_tank->Load(0.0f, 0.0f, enemy_tank_data);
			enemy_tank->SetEnemyTankSpawner(game_master);
			enemy_tank->Despawn();

			uint16_t enemy_tank_bullet_count = enemy_tank_data.at("bullet_count");
			auto& bullet_data = enemy_tank_data.at("bullet");
			std::string bullet_default_name = bullet_data.at("name");

			for (uint16_t bullet_counter = 1; bullet_counter <= enemy_tank_bullet_count; bullet_counter++) {
				std::stringstream bullet_name_stream;
				bullet_name_stream
					<< enemy_tank_name
					<< "_" << bullet_default_name
					<< "_" << bullet_counter;
				std::string bullet_name = bullet_name_stream.str();

				auto bullet = dynamic_cast<pEnemyBullet>(CreateGameObject(ENEMY_BULLET, bullet_name));
				bullet->Load(0.0, 0.0, bullet_data);
				bullet->SetTank(enemy_tank);
				bullet->Impact();
			}
			break;
		}

		default:break;
		}
	}

	// TERRAIN PREFAB
	auto& brick_data = data.at("brick");
	std::string brick_default_name = brick_data.at("name");

	auto& steel_data = data.at("steel");
	std::string steel_default_name = steel_data.at("name");

	auto& tree_data = data.at("tree");
	std::string tree_default_name = tree_data.at("name");

	auto& ice_data = data.at("ice");
	std::string ice_default_name = ice_data.at("name");

	auto& water_data = data.at("water");
	std::string water_default_name = water_data.at("name");

	// HEAD_QUARTER
	auto& headquarter_data = data.at("headquarter");
	std::string headquarter_name = headquarter_data.at("name");
	float headquarter_pos_x = headquarter_data.at("x");
	float headquarter_pos_y = headquarter_data.at("y");
	auto headquarter = dynamic_cast<pHeadquarter>(CreateGameObject(HEADQUARTER, headquarter_name));
	headquarter->Load(headquarter_pos_x, headquarter_pos_y, headquarter_data);

	uint8_t fence_counter = 0;
	for (auto& hq_fence_data : headquarter_data.at("fence")) {
		float x = hq_fence_data.at("x");
		float y = hq_fence_data.at("y");

		std::stringstream brick_name_stream;
		brick_name_stream
			<< headquarter_name
			<< "_" << brick_default_name
			<< "_" << fence_counter;
		std::string brick_name = brick_name_stream.str();

		auto brick = dynamic_cast<pBrick>(CreateGameObject(BRICK, brick_name));
		brick->Load(x, y, brick_data);
		brick->SetFenceSpawner(headquarter);
		brick->Spawn();

		std::stringstream steel_name_stream;
		steel_name_stream
			<< headquarter_name
			<< "_" << steel_default_name
			<< "_" << fence_counter;
		std::string steel_name = steel_name_stream.str();

		auto steel = dynamic_cast<pSteel>(CreateGameObject(STEEL, steel_name));
		steel->Load(x, y, steel_data);
		steel->SetFenceSpawner(headquarter);
		steel->Despawn();

		fence_counter += 1;
	}

	// BOUND
	{
		auto& left_bound_data = data.at("left_bound");
		std::string left_bound_name = left_bound_data.at("name");
		float left_bound_pos_x = left_bound_data.at("x");
		float left_bound_pos_y = left_bound_data.at("y");
		auto left_bound = dynamic_cast<pBound>(CreateGameObject(BOUND, left_bound_name));
		left_bound->Load(left_bound_pos_x, left_bound_pos_y, left_bound_data);

		auto& top_bound_data = data.at("top_bound");
		std::string top_bound_name = top_bound_data.at("name");
		float top_bound_pos_x = top_bound_data.at("x");
		float top_bound_pos_y = top_bound_data.at("y");
		auto top_bound = dynamic_cast<pBound>(CreateGameObject(BOUND, top_bound_name));
		top_bound->Load(top_bound_pos_x, top_bound_pos_y, top_bound_data);

		auto& right_bound_data = data.at("right_bound");
		std::string right_bound_name = right_bound_data.at("name");
		float right_bound_pos_x = right_bound_data.at("x");
		float right_bound_pos_y = right_bound_data.at("y");
		auto right_bound = dynamic_cast<pBound>(CreateGameObject(BOUND, right_bound_name));
		right_bound->Load(right_bound_pos_x, right_bound_pos_y, right_bound_data);

		auto& bottom_bound_data = data.at("bottom_bound");
		std::string bottom_bound_name = bottom_bound_data.at("name");
		float bottom_bound_pos_x = bottom_bound_data.at("x");
		float bottom_bound_pos_y = bottom_bound_data.at("y");
		auto bottom_bound = dynamic_cast<pBound>(CreateGameObject(BOUND, bottom_bound_name));
		bottom_bound->Load(bottom_bound_pos_x, bottom_bound_pos_y, bottom_bound_data);
	}

	// MAP
	{
		auto& map_data = data.at("map");
		uint32_t columns = uint32_t(map_data.at("columns"));
		uint32_t rows = uint32_t(map_data.at("rows"));
		float tile_width = float(map_data.at("tile_width"));
		float tile_height = float(map_data.at("tile_height"));
		float offset_x = float(map_data.at("offset_x"));
		float offset_y = float(map_data.at("offset_y"));

		std::vector<int32_t> tiles;
		for (auto& tile : map_data.at("data")) {
			tiles.push_back(tile);
		}

		for (int32_t tile = 0; tile < tiles.size(); tile++) {
			int32_t x = tile % columns;
			int32_t y = rows - (tile / columns) - 1;

			float position_x = (x * tile_width) + offset_x;
			float position_y = (y * tile_height) + offset_y;

			int32_t type = tiles[tile];
			switch (type) {

			case 0: { // BLANK
				break;
			}

			case 1: { // BRICK
				std::stringstream brick_stream;
				brick_stream
					<< brick_default_name
					<< "_" << tile;
				std::string brick_name = brick_stream.str();

				auto brick = dynamic_cast<pBrick>(CreateGameObject(BRICK, brick_name));
				brick->Load(position_x, position_y, brick_data);

				break;
			}

			case 2: { // STEEL
				std::stringstream steel_stream;
				steel_stream
					<< steel_default_name
					<< "_" << tile;
				std::string steel_name = steel_stream.str();

				auto steel = dynamic_cast<pSteel>(CreateGameObject(STEEL, steel_name));
				steel->Load(position_x, position_y, steel_data);

				break;
			}

			case 3: { // TREE
				std::stringstream tree_stream;
				tree_stream
					<< tree_default_name
					<< "_" << tile;
				std::string tree_name = tree_stream.str();

				auto tree = dynamic_cast<pTree>(CreateGameObject(TREE, tree_name));
				tree->Load(position_x, position_y, tree_data);

				break;
			}

			case 4: { // WATER
				std::stringstream water_stream;
				water_stream
					<< water_default_name
					<< "_" << tile;
				std::string water_name = water_stream.str();

				auto water = dynamic_cast<pWater>(CreateGameObject(WATER, water_name));
				water->Load(position_x, position_y, water_data);

				break;
			}

			case 5: { // ICE
				std::stringstream ice_stream;
				ice_stream
					<< ice_default_name
					<< "_" << tile;
				std::string ice_name = ice_stream.str();

				auto ice = dynamic_cast<pIce>(CreateGameObject(ICE, ice_name));
				ice->Load(position_x, position_y, ice_data);

				break;
			}

			default: {
				break;
			}

			}
		}
	}

	GetGameServer().ResetPlayerReadyStatus();
	SendLoadPacket();
}

void CPlayScene::Unload() {
	CGameObjectManager::ClearGameObjects();
}

void CPlayScene::Update(float elapsed_ms) {
	switch (state)
	{
	case CPlayScene::EState::LOADING: {
		if (GetGameServer().AllPlayersReady()) {
			GetGameServer().ResetPlayerReadyStatus();
			SendStartGamePacket();
			SetState(EState::RUN);
		}
		break;
	}

	case CPlayScene::EState::RUN: {

		if (CServerTickCounter::IsRollback()) {
			Tick last_tick = GetLatestTick() - 1;
			Tick deserialize_tick = GetRollbackTick() - 1;
			Tick rolling_back_tick = GetRollbackTick();

			CCommandManager::TrimServerCommandsOnly(rolling_back_tick, last_tick);
			CRecordManager::TrimRecords(rolling_back_tick, last_tick);
			CRecordManager::Deserialze(deserialize_tick);

			for (rolling_back_tick; rolling_back_tick <= last_tick; rolling_back_tick++) {
				CCommandManager::ExecuteCommands(rolling_back_tick);
				CUpdateManager::Update(elapsed_ms);
				CWorld::UpdatePhysicsWorld(elapsed_ms);
				CEventManager::HandleEvent();
				CRecordManager::Serialize(rolling_back_tick);
			}

			CServerTickCounter::SetRollback(false);
			CServerTickCounter::SetRollbackTick(rolling_back_tick);
		}

		Tick latest_tick = CServerTickCounter::GetLatestTick();

		CInputManager::HandleInput(latest_tick);
		CCommandManager::ExecuteCommands(latest_tick);
		CUpdateManager::Update(elapsed_ms);
		CWorld::UpdatePhysicsWorld(elapsed_ms);
		CEventManager::HandleEvent();
		CRecordManager::Serialize(latest_tick);

		Tick tick_per_game_state = CServerTickCounter::GetTickPerGameState();
		Tick drop_tick = latest_tick - (tick_per_game_state * 2);

		CCommandManager::TrimCommands(drop_tick);
		CRecordManager::TrimRecords(drop_tick);

		if (
			latest_tick > tick_per_game_state
			&& latest_tick % tick_per_game_state == 0
			)
		{
			//SendStatePacket();
		}

		CServerTickCounter::IncreaseLatestTick();

		break;
	}

	case CPlayScene::EState::DONE: {
		break;
	}
	default: break;
	}
}

void CPlayScene::Render(sf::RenderWindow& window) {
	CRenderManager::Render(window);
}

void CPlayScene::OnConnect(ClientID id) {
}

void CPlayScene::OnDisconnect(ClientID id) {
}

bool CPlayScene::ProcessPacket(std::shared_ptr<CPacket> packet) {
	switch (packet->GetPacketType()) {
	case DONE_LOAD: {
		HandleLoadDonePacket(packet.get());
		return true;
	}

	case PLAYER_MOVE: {
		HandleMovePacket(packet.get());
		return true;
	}

	case PLAYER_SHOOT: {
		HandleShootPacket(packet.get());
		return true;
	}

	default: return true;
	}
}

void CPlayScene::SendLoadPacket() {
	SendHeadLoadPacket();

	for (auto& game_object_container : GetAllGameObject()) {
		GameObjectID id = game_object_container.first;
		SendBodyLoadPacket(id);
	}

	SendEndLoadPacket();
}

void CPlayScene::SendHeadLoadPacket() {
	auto packet = std::make_shared<CPacket>(HEAD_LOAD);

	Tick tick_per_game_state = GetTickPerGameState();
	*packet << tick_per_game_state;

	float gravity_x;
	float gravity_y;
	GetGravity(gravity_x, gravity_y);
	*packet << gravity_x << gravity_y;

	GetGameServer().SendAll(packet);
}

void CPlayScene::SendBodyLoadPacket(GameObjectID id) {
	auto packet = std::make_shared<CPacket>(BODY_LOAD);

	auto game_object = GetGameObject(id);
	ActorType type = game_object->GetType();
	*packet << type;

	std::string name = game_object->GetName();
	*packet << name;

	auto network_object = dynamic_cast<pNetworkObject>(game_object);
	NetworkID network_id = network_object->GetNetworkID();
	*packet << network_id;

	auto server_object = dynamic_cast<pServerObject>(game_object);
	server_object->PackLoadPacket(packet.get());

	GetGameServer().SendAll(packet);
}

void CPlayScene::SendEndLoadPacket() {
	auto packet = std::make_shared<CPacket>(END_LOAD);
	GetGameServer().SendAll(packet);
}

void CPlayScene::SendStartGamePacket() {
	auto packet = std::make_shared<CPacket>(START_GAME);
	GetGameServer().SendAll(packet);
}

void CPlayScene::SendStatePacket() {
	auto packet = std::make_shared<CPacket>(STATE);

	Tick send_tick = GetLatestTick() - GetTickPerGameState();
	*packet << send_tick;

	auto& records = CRecordManager::GetRecordsAtTick(send_tick);

	uint16_t records_count = records.size();
	*packet << records_count;

	for (auto record : records) {
		NetworkID network_id = record->network_object_id;
		*packet << network_id;

		record->Pack(packet.get());
	}

	GetGameServer().SendAll(packet);
}

void CPlayScene::SendEndGamePacket() {
	auto packet = std::make_shared<CPacket>(END_GAME);

	GetGameServer().SendAll(packet);
}

void CPlayScene::SendStartNextLevelPacket() {
	auto packet = std::make_shared<CPacket>(START_PLAY_SCENE);

	GetGameServer().SendAll(packet);
}

void CPlayScene::SendBackToLobbyPacket() {
	auto packet = std::make_shared<CPacket>(BACK_TO_LOBBY_SCENE);

	GetGameServer().SendAll(packet);
}

void CPlayScene::HandleLoadDonePacket(pPacket packet) {
	PlayerID id;
	*packet >> id;
	GetGameServer().PlayerReady(id);
}

void CPlayScene::HandleMovePacket(pPacket packet) {
	Tick receive_tick;
	*packet >> receive_tick;

	if (receive_tick < GetLatestTick() - (GetTickPerGameState() * 2))
		return;



}

void CPlayScene::HandleShootPacket(pPacket packet) {
	Tick receive_tick;
	*packet >> receive_tick;

	if (receive_tick < GetLatestTick() - (GetTickPerGameState() * 2))
		return;


}
