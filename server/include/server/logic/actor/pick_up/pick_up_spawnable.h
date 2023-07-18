#pragma once
#ifndef __PICK_UP_SPAWNABLE_H__
#define __PICK_UP_SPAWNABLE_H__

#include "common.h"

class CPickUpSpawner;
class CPickUpSpawnable {
private:
	CPickUpSpawner* pick_up_spawner = nullptr;
	bool is_spawned;

public:
	void SetPickUpSpawner(CPickUpSpawner* spawner);
	bool IsSpawned() { return is_spawned; }

	void Spawn(float x, float y);
	void Despawn();

	virtual void OnSpawn(float x, float y) = 0;
	virtual void OnDespawn() = 0;
};
typedef CPickUpSpawnable* pPickUpSpawnable;

#endif // !__PICK_UP_SPAWNABLE_H__
