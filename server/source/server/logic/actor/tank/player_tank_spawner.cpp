#include "server/logic/actor/tank/player_tank_spawner.h"

void CPlayerTankSpawner::AddPlayerTankSpawnable(PlayerID id, pPlayerTankSpawnable spawnable) {
	spawnables[id] = spawnable;
}

void CPlayerTankSpawner::AddSpawnPosition(PlayerID id, float x, float y) {
	spawn_positions[id] = std::make_pair(x, y);
}

void CPlayerTankSpawner::Clear() {
	spawnables.clear();
	spawn_positions.clear();
}

void CPlayerTankSpawner::LoadPlayerTankSpawner(json& data) {
	for (auto& player_spawn_data : data.at("player_spawn")) {
		PlayerID id = player_spawn_data.at("id");
		float x = player_spawn_data.at("x");
		float y = player_spawn_data.at("y");
		AddSpawnPosition(id, x, y);
	}
}

void CPlayerTankSpawner::SpawnPlayerTank(PlayerID id) {
	auto player_tank = spawnables[id];
	auto& spawn_position = spawn_positions[id];

	if (!player_tank->IsSpawned()) {
		player_tank->Spawn(spawn_position.first, spawn_position.second);
	}
}
