#pragma once
#ifndef __WORLD_H__
#define __WORLD_H__

#include "common.h"
#include "engine/framework/network/packet.h"

class CWorld : public b2ContactListener {
private:
	b2World* physics_world = nullptr;
	float gravity_x;
	float gravity_y;

public:
	CWorld();
	virtual ~CWorld();

	b2World* GetPhysicsWorld() { return physics_world; }
	b2World* CreatePhysicsWorld(float gravity_x, float gravity_y);
	void GetGravity(float& x, float& y) { x = gravity_x; y = gravity_y; }
	void DestroyPhysicsWorld();

	void LoadWorldFromJson(json& data);
	void PackWorldLoadPacket(pPacket packet);
	void LoadWorldFromPacket(pPacket packet);

	void UpdatePhysicsWorld(float elapsed_ms);

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
};

#endif // !__WORLD_H__