#pragma once
#ifndef __ENEMY_TANK_SPAWNABLE_H__
#define __ENEMY_TANK_SPAWNABLE_H__

#include "common.h"

class CEnemyTankSpawner;
typedef CEnemyTankSpawner* pEnemyTankSpawner;

class CEnemyTankSpawnable {
private:
	pEnemyTankSpawner enemy_tank_spawner = nullptr;
	bool is_spawned = false;

public:
	void SetEnemyTankSpawner(pEnemyTankSpawner spawner);

	void SetSpawned(bool value) { is_spawned = value; }
	bool IsSpawned() { return is_spawned; }

	void Spawn(float x, float y);
	void Despawn();

	virtual void OnSpawn(float x, float y) = 0;
	virtual void OnDespawn() = 0;
};
typedef CEnemyTankSpawnable* pEnemyTankSpawnable;

#endif // !__ENEMY_TANK_SPAWNABLE_H__
