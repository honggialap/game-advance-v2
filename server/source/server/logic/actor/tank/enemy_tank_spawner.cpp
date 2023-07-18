#include "server/logic/actor/tank/enemy_tank_spawner.h"

void CEnemyTankSpawner::AddEnemyTankSpawnable(pEnemyTankSpawnable spawnable) {
	spawnables.push_back(spawnable);
}

void CEnemyTankSpawner::AddSpawnPosition(float x, float y) {
	spawn_positions.push_back(std::make_pair(x, y));
}

void CEnemyTankSpawner::Clear() {
	spawnables.clear();
	spawn_positions.clear();
}

void CEnemyTankSpawner::LoadEnemyTankSpawner(json& data) {
	for (auto& enemy_spawn_data : data.at("enemy_spawn")) {
		float x = enemy_spawn_data.at("x");
		float y = enemy_spawn_data.at("y");
		AddSpawnPosition(x, y);
	}
}

void CEnemyTankSpawner::SpawnEnemyTank() {
	size_t spawn_position_index = rand() % spawn_positions.size();
	auto enemy_tank = spawnables[current_index];
	auto& spawn_position = spawn_positions[spawn_position_index];

	if (!enemy_tank->IsSpawned()) {
		enemy_tank->Spawn(spawn_position.first, spawn_position.second);
	}

	current_index += 1;
	if (current_index >= spawnables.size()) {
		current_index = 0;
	}
}
