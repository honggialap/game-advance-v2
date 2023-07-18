#include "server/logic/actor/pick_up/pick_up_spawnable.h"
#include "server/logic/actor/pick_up/pick_up_spawner.h"

void CPickUpSpawnable::SetPickUpSpawner(CPickUpSpawner* spawner) {
	pick_up_spawner = spawner;
	pick_up_spawner->AddPickUpSpawnable(this);
}

void CPickUpSpawnable::Spawn(float x, float y) {
	is_spawned = true;
	OnSpawn(x, y);
}

void CPickUpSpawnable::Despawn() {
	is_spawned = false;
	OnDespawn();
}
