#include "server/logic/actor/tank/player_tank_spawnable.h"
#include "server/logic/actor/tank/player_tank_spawner.h"

void CPlayerTankSpawnable::SetPlayerTankSpawner(PlayerID id, pPlayerTankSpawner spawner) {
	player_tank_spawner = spawner;
	player_tank_spawner->AddPlayerTankSpawnable(id, this);
}

void CPlayerTankSpawnable::Spawn(float x, float y) {
	is_spawned = true;
	OnSpawn(x, y);
}

void CPlayerTankSpawnable::Despawn() {
	is_spawned = false;
	OnDespawn();
}