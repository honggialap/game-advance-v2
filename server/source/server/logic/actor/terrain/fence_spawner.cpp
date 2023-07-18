#include "server/logic/actor/terrain/fence_spawner.h"

void CFenceSpawner::AddBrick(pBrick brick) {
	bricks.push_back(brick);
}

void CFenceSpawner::AddSteel(pSteel steel) {
	steels.push_back(steel);
}

void CFenceSpawner::Clear() {
	bricks.clear();
	steels.clear();
}

void CFenceSpawner::SpawnBrick() {
	for (auto steel : steels) {
		steel->Despawn();
	}

	for (auto brick : bricks) {
		brick->Spawn();
	}
}

void CFenceSpawner::SpawnSteel() {
	for (auto brick : bricks) {
		brick->Despawn();
	}

	for (auto steel : steels) {
		steel->Spawn();
	}
}
