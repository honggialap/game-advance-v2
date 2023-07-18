#include "engine/framework/physics/world.h"
#include "engine/framework/physics/body.h"

CWorld::CWorld() {
}

CWorld::~CWorld() {
	DestroyPhysicsWorld();
}


b2World* CWorld::CreatePhysicsWorld(float gravity_x, float gravity_y) {
	if (physics_world) return physics_world;

	this->gravity_x = gravity_x;
	this->gravity_y = gravity_y;

	return physics_world = new b2World(
		b2Vec2(
			gravity_x / PIXEL_PER_METER
			, gravity_y / PIXEL_PER_METER
		)
	);
}

void CWorld::DestroyPhysicsWorld() {
	if (physics_world)
		delete physics_world; physics_world = nullptr;
}

void CWorld::LoadWorldFromJson(json& data) {
	if (!data.contains("world")) return;
	auto& world_data = data.at("world");
	float gravity_x = world_data.at("gravity_x");
	float gravity_y = world_data.at("gravity_y");
	CreatePhysicsWorld(gravity_x, gravity_y);
}

void CWorld::PackWorldLoadPacket(pPacket packet)
{
}

void CWorld::LoadWorldFromPacket(pPacket packet)
{
}

void CWorld::UpdatePhysicsWorld(float elapsed_ms) {
	physics_world->Step(elapsed_ms, 6, 3);
}

void CWorld::BeginContact(b2Contact* contact) {
	auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (dataA && dataB) {
		auto objectA = static_cast<pBody>(dataA);
		auto objectB = static_cast<pBody>(dataB);
		objectA->OnCollisionEnter(objectB);
		objectB->OnCollisionEnter(objectA);
	}
}

void CWorld::EndContact(b2Contact* contact) {
	auto dataA = (void*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	auto dataB = (void*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (dataA && dataB) {
		auto objectA = static_cast<pBody>(dataA);
		auto objectB = static_cast<pBody>(dataB);
		objectA->OnCollisionExit(objectB);
		objectB->OnCollisionExit(objectA);
	}
}
