#ifndef __PLAYER_TANK_SPAWNER_H__
#define __PLAYER_TANK_SPAWNER_H__

#include "player_tank_spawnable.h"

class CPlayerTankSpawner {
private:
	std::map<PlayerID, pPlayerTankSpawnable> spawnables;
	std::map<PlayerID, std::pair<float, float>> spawn_positions;

public:
	void AddPlayerTankSpawnable(PlayerID id, pPlayerTankSpawnable spawnable);
	void AddSpawnPosition(PlayerID id, float x, float y);
	void Clear();

	void LoadPlayerTankSpawner(json& data);

	void SpawnPlayerTank(PlayerID id);
};
typedef CPlayerTankSpawner* pPlayerTankSpawner;

#endif // !__ENEMY_TANK_SPAWNER_H__
