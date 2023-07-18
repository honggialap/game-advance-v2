#include "server/logic/actor/tank/enemy_tank_spawnable.h"
#include "server/logic/actor/tank/enemy_tank_spawner.h"

void CEnemyTankSpawnable::SetEnemyTankSpawner(pEnemyTankSpawner spawner) {
	enemy_tank_spawner = spawner;
	enemy_tank_spawner->AddEnemyTankSpawnable(this);
}

void CEnemyTankSpawnable::Spawn(float x, float y) {
	is_spawned = true;
	OnSpawn(x, y);
}

void CEnemyTankSpawnable::Despawn() {
	is_spawned = false;
	OnDespawn();
}
