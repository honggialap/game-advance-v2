#pragma once
#ifndef __FENCE_SPAWNER_H__
#define __FENCE_SPAWNER_H__

#include "brick.h"
#include "steel.h"

class CFenceSpawner {
private:
	std::vector<pBrick> bricks;
	std::vector<pSteel> steels;

public:
	void AddBrick(pBrick brick);
	void AddSteel(pSteel steel);
	void Clear();

	void SpawnBrick();
	void SpawnSteel();
};
typedef CFenceSpawner* pFenceSpawner;

#endif // !__PICK_UP_SPAWNER_H__
