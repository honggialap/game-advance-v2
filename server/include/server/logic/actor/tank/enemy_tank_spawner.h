#pragma once
#ifndef __ENEMY_TANK_SPAWNER_H__
#define __ENEMY_TANK_SPAWNER_H__

#include "enemy_tank_spawnable.h"

class CEnemyTankSpawner {
private:
	std::vector<pEnemyTankSpawnable> spawnables;
	std::vector<std::pair<float, float>> spawn_positions;
	size_t current_index = 0;

public:
	void AddEnemyTankSpawnable(pEnemyTankSpawnable spawnable);
	void AddSpawnPosition(float x, float y);
	void Clear();

	void LoadEnemyTankSpawner(json& data);

	void SpawnEnemyTank();
};
typedef CEnemyTankSpawner* pEnemyTankSpawner;

#endif // !__ENEMY_TANK_SPAWNER_H__
