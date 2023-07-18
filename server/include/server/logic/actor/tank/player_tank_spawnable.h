#pragma once
#ifndef __PLAYER_TANK_SPAWNABLE_H__
#define __PLAYER_TANK_SPAWNABLE_H__

#include "common.h"

class CPlayerTankSpawner;
typedef CPlayerTankSpawner* pPlayerTankSpawner;

class CPlayerTankSpawnable {
private:
	pPlayerTankSpawner player_tank_spawner = nullptr;
	bool is_spawned = false;

public:
	void SetPlayerTankSpawner(PlayerID id, pPlayerTankSpawner spawner);
	bool IsSpawned() { return is_spawned; }

	void Spawn(float x, float y);
	void Despawn();

	virtual void OnSpawn(float x, float y) = 0;
	virtual void OnDespawn() = 0;
};
typedef CPlayerTankSpawnable* pPlayerTankSpawnable;



#endif // !__PLAYER_TANK_SPAWNABLE_H__
