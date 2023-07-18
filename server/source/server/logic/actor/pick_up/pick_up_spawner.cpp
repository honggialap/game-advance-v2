#include "server/logic/actor/pick_up/pick_up_spawner.h"


void CPickUpSpawner::AddPickUpSpawnable(pPickUpSpawnable spawnable) {
	spawnables.push_back(spawnable);
}

void CPickUpSpawner::AddSpawnPosition(float x, float y) {
	spawn_positions.push_back(std::make_pair(x, y));
}

void CPickUpSpawner::Clear() {
	spawnables.clear();
	spawn_positions.clear();
}

void CPickUpSpawner::LoadPickUpSpawner(json& data) {
	for (auto& pick_up_data : data.at("pick_up_spawn")) {
		float x = pick_up_data.at("x");
		float y = pick_up_data.at("y");
		AddSpawnPosition(x, y);
	}
}

void CPickUpSpawner::SpawnPickUp() {
	bool spawn_success = false;
	while (!spawn_success) {
		size_t pick_up_index = rand() % spawnables.size();
		size_t spawn_position_index = rand() % spawn_positions.size();

		auto pick_up = spawnables[pick_up_index];
		if (pick_up->IsSpawned()) {
			continue;
		}

		auto& spawn_position = spawn_positions[spawn_position_index];
		pick_up->Spawn(spawn_position.first, spawn_position.second);
		spawn_success = true;
	}
}