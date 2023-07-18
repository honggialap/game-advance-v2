#pragma once
#ifndef __PICK_UP_SPAWNER_H__
#define __PICK_UP_SPAWNER_H__

#include "pick_up_spawnable.h"

class CPickUpSpawner {
private:
	std::vector<pPickUpSpawnable> spawnables; 
	std::vector<std::pair<float, float>> spawn_positions;

public:
	void AddPickUpSpawnable(pPickUpSpawnable spawnable);
	void AddSpawnPosition(float x, float y);
	void Clear();

	void LoadPickUpSpawner(json& data);

	void SpawnPickUp();
};
typedef CPickUpSpawner* pPickUpSpawner;

#endif // !__PICK_UP_SPAWNER_H__
