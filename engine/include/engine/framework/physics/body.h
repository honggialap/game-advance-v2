#pragma once
#ifndef __BODY_H__
#define __BODY_H__

#include "common.h"
#include "engine/framework/network/packet.h"

class CWorld;
class CBody {
private:
	CWorld& world;
	b2Body* physics_body = nullptr;

	float width = 0.0f;
	float height = 0.0f;
	
	float offset_x = 0.0f;
	float offset_y = 0.0f;

public:
	CBody(CWorld& world);
	virtual ~CBody() = 0;

	CWorld& GetWorld() { return world; }

	void LoadBodyFromJson(json& data, float position_x = 0.0f, float position_y = 0.0f);
	void PackBodyLoadPacket(pPacket packet);
	void LoadBodyFromPacket(pPacket packet);

	b2Body* GetPhysicsBody() { return physics_body; }
	b2Body* CreatePhysicsBody(
		b2BodyType body_type
		, float position_x, float position_y
	);
	void DestroyPhysicsBody();

	void SetBodyPosition(float x, float y);
	void GetBodyPosition(float& x, float& y);

	void SetBodyVelocity(float vx, float vy);
	void GetBodyVelocity(float& vx, float& vy);

	b2Fixture* GetCollider();
	b2Fixture* CreateCollider(float witdh, float height, float offset_x, float offset_y, float density);
	void DestroyCollider();

	void SetColliderSize(float width, float height, float offset_x, float offset_y);
	void GetColliderSize(float& width, float& height, float& offset_x, float& offset_y);

	virtual void OnCollisionEnter(CBody* other) = 0;
	virtual void OnCollisionExit(CBody* other) = 0;
};
typedef CBody* pBody;

#endif // !__BODY_H__
