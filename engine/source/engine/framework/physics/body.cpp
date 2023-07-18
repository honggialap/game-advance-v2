#include "engine/framework/physics/body.h"
#include "engine/framework/physics/world.h"

CBody::CBody(CWorld& world)
	: world(world) {
}

CBody::~CBody() {
}

void CBody::LoadBodyFromJson(json& data, float position_x, float position_y) {
	if (!data.contains("body")) return;
	auto& body_data = data.at("body");

	b2BodyType body_type = body_data.at("body_type");
	auto body = CreatePhysicsBody(body_type, position_x, position_y);

	if (body_data.contains("enable")) {
		bool is_enabled = body_data.at("enable");
		body->SetEnabled(is_enabled);
	}

	if (body_data.contains("awake")) {
		bool is_awake = body_data.at("awake");
		body->SetAwake(is_awake);
	}

	if (body_data.contains("bullet")) {
		bool is_bullet = body_data.at("bullet");
		body->SetBullet(is_bullet);
	}

	if (body_data.contains("fixed_rotation")) {
		bool is_fixed_rotation = body_data.at("fixed_rotation");
		body->SetFixedRotation(is_fixed_rotation);
	}

	float width = body_data.at("width");
	float height = body_data.at("height");
	float offset_x = body_data.at("offset_x");
	float offset_y = body_data.at("offset_y");

	float density = 1.0f;
	if (body_data.contains("density")) {
		density = body_data.at("density");
	}

	auto collider = CreateCollider(width, height, offset_x, offset_y, density);

	b2Filter filter;

	if (body_data.contains("category_bits")) {
		uint16_t category_bits = body_data.at("category_bits");
		filter.categoryBits = category_bits;
	}

	if (body_data.contains("mask_bits")) {
		uint16_t mask_bits = body_data.at("mask_bits");
		filter.maskBits = mask_bits;
	}

	if (body_data.contains("group_index")) {
		int16_t group_index = body_data.at("group_index");
		filter.groupIndex = group_index;
	}

	collider->SetFilterData(filter);

	if (body_data.contains("sensor")) {
		bool is_sensor = body_data.at("sensor");
		collider->SetSensor(is_sensor);
	}

	if (body_data.contains("friction")) {
		float friction = body_data.at("friction");
		collider->SetFriction(friction);
	}

	if (body_data.contains("restitution")) {
		float restitution = body_data.at("restitution");
		collider->SetRestitution(restitution);
	}

	if (body_data.contains("restitution_threshold")) {
		float restitution_threshold = body_data.at("restitution_threshold");
		collider->SetRestitutionThreshold(restitution_threshold);
	}

}

void CBody::PackBodyLoadPacket(pPacket packet) {
	int16_t body_type = physics_body->GetType();
	*packet << body_type;

	float x;
	float y;
	GetBodyPosition(x, y);
	*packet << x << y;

	bool is_enabled = physics_body->IsEnabled();
	*packet << is_enabled;

	bool is_awake = physics_body->IsAwake();
	*packet << is_awake;

	bool is_bullet = physics_body->IsBullet();
	*packet << is_bullet;

	bool is_fixed_rotation = physics_body->IsFixedRotation();
	*packet << is_fixed_rotation;

	float width;
	float height;
	float offset_x;
	float offset_y;
	GetColliderSize(width, height, offset_x, offset_y);
	*packet << width << height << offset_x << offset_y;

	float density = GetCollider()->GetDensity();
	*packet << density;

	b2Filter filter = GetCollider()->GetFilterData();

	uint16_t category_bits = filter.categoryBits;
	*packet << category_bits;

	uint16_t mask_bits = filter.maskBits;
	*packet << mask_bits;

	int16_t group_index = filter.groupIndex;
	*packet << group_index;

	bool is_sensor = GetCollider()->IsSensor();
	*packet << is_sensor;

	float friction = GetCollider()->GetFriction();
	*packet << friction;

	float restitution = GetCollider()->GetRestitution();
	*packet << restitution;

	float restitution_threshold = GetCollider()->GetRestitutionThreshold();
	*packet << restitution_threshold;
}

void CBody::LoadBodyFromPacket(pPacket packet) {
	int16_t body_type;
	*packet >> body_type;

	float position_x;
	float position_y;
	*packet >> position_x >> position_y;

	auto body = CreatePhysicsBody(b2BodyType(body_type), position_x, position_y);

	bool is_enabled;
	*packet >> is_enabled;
	body->SetEnabled(is_enabled);

	bool is_awake;
	*packet >> is_awake;
	body->SetAwake(is_awake);

	bool is_bullet;
	*packet >> is_bullet;
	body->SetBullet(is_bullet);

	bool is_fixed_rotation;
	*packet >> is_fixed_rotation;
	body->SetFixedRotation(is_fixed_rotation);

	float width;
	float height;
	float offset_x;
	float offset_y;
	*packet >> width >> height >> offset_x >> offset_y;

	float density;
	*packet >> density;

	auto collider = CreateCollider(width, height, offset_x, offset_y, density);

	b2Filter filter;

	uint16_t category_bits;
	*packet >> category_bits;
	filter.categoryBits = category_bits;

	uint16_t mask_bits;
	*packet >> mask_bits;
	filter.maskBits = mask_bits;

	int16_t group_index;
	*packet >> group_index;
	filter.groupIndex = group_index;

	collider->SetFilterData(filter);

	bool is_sensor;
	*packet >> is_sensor;
	collider->SetSensor(is_sensor);

	float friction;
	*packet >> friction;
	collider->SetFriction(friction);

	float restitution;
	*packet >> restitution;
	collider->SetRestitution(restitution);

	float restitution_threshold;
	*packet >> restitution_threshold;
	collider->SetRestitutionThreshold(restitution_threshold);
}

b2Body* CBody::CreatePhysicsBody(
	b2BodyType body_type
	, float position_x, float position_y
) {
	if (physics_body) DestroyPhysicsBody();

	b2BodyDef body_def;

	body_def.type = body_type;
	body_def.position.x = position_x / PIXEL_PER_METER;
	body_def.position.y = position_y / PIXEL_PER_METER;
	body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);

	physics_body = world.GetPhysicsWorld()->CreateBody(&body_def);
	return physics_body;
}

void CBody::DestroyPhysicsBody() {
	if (!physics_body) return;

	world.GetPhysicsWorld()->DestroyBody(physics_body);
	physics_body = nullptr;
}

void CBody::SetBodyPosition(float x, float y) {
	if (!physics_body) return;

	physics_body->SetTransform(
		b2Vec2(x / PIXEL_PER_METER, y / PIXEL_PER_METER)
		, 0.0f
	);

}

void CBody::GetBodyPosition(float& x, float& y) {
	if (!physics_body) return;

	auto& transform = physics_body->GetTransform();
	x = transform.p.x * PIXEL_PER_METER;
	y = transform.p.y * PIXEL_PER_METER;
}

void CBody::SetBodyVelocity(float vx, float vy) {
	if (!physics_body) return;

	physics_body->SetLinearVelocity(
		b2Vec2(vx / PIXEL_PER_METER, vy / PIXEL_PER_METER)
	);
}

void CBody::GetBodyVelocity(float& vx, float& vy) {
	if (!physics_body) return;

	auto& velocity = physics_body->GetLinearVelocity();
	vx = velocity.x * PIXEL_PER_METER;
	vy = velocity.y * PIXEL_PER_METER;
}

b2Fixture* CBody::GetCollider() {
	if (!physics_body) return nullptr;
	return physics_body->GetFixtureList();
}

b2Fixture* CBody::CreateCollider(float width, float height, float offset_x, float offset_y, float density) {
	if (!physics_body) return nullptr;

	b2PolygonShape shape;
	shape.SetAsBox(
		(width / 2.0) / PIXEL_PER_METER
		, (height / 2.0) / PIXEL_PER_METER
		, b2Vec2(offset_x / PIXEL_PER_METER, offset_y / PIXEL_PER_METER)
		, 0.0f
	);

	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;
	fixture_def.density = density;

	return physics_body->CreateFixture(&fixture_def);
}

void CBody::DestroyCollider() {
	if (!physics_body) return;
	if (!physics_body->GetFixtureList()) return;

	physics_body->DestroyFixture(
		physics_body->GetFixtureList()
	);
}

void CBody::SetColliderSize(float width, float height, float offset_x, float offset_y) {
	if (!physics_body) return;
	if (!GetCollider()) return;
	auto old_fixture = GetCollider();

	uint16_t category_bits = old_fixture->GetFilterData().categoryBits;
	uint16_t mask_bits = old_fixture->GetFilterData().maskBits;
	int16_t group_index = old_fixture->GetFilterData().groupIndex;

	bool is_sensor = old_fixture->IsSensor();
	float density = old_fixture->GetDensity();
	float friction = old_fixture->GetFriction();
	float restitution = old_fixture->GetRestitution();
	float restitution_threshold = old_fixture->GetRestitutionThreshold();


	physics_body->DestroyFixture(
		physics_body->GetFixtureList()
	);

	auto new_fixture = CreateCollider(width, height, offset_x, offset_y, density);

	b2Filter new_filter;
	new_filter.categoryBits = category_bits;
	new_filter.maskBits = mask_bits;
	new_filter.groupIndex = group_index;

	new_fixture->SetFilterData(new_filter);
	new_fixture->SetSensor(is_sensor);
	new_fixture->SetFriction(friction);
	new_fixture->SetRestitution(restitution);
	new_fixture->SetRestitutionThreshold(restitution_threshold);
}

void CBody::GetColliderSize(float& width, float& height, float& offset_x, float& offset_y) {
	if (!GetCollider()) return;

	auto shape = static_cast<b2PolygonShape*>(GetCollider()->GetShape());
	b2Vec2 b2_bottom_left = shape->m_vertices[0];
	b2Vec2 b2_bottom_right = shape->m_vertices[1];
	b2Vec2 b2_top_right = shape->m_vertices[2];
	b2Vec2 b2_top_left = shape->m_vertices[3];
	b2Vec2 b2_centroid = shape->m_centroid;

	width = (b2_bottom_right.x - b2_bottom_left.x) * PIXEL_PER_METER;
	height = (b2_top_left.y - b2_bottom_left.y) * PIXEL_PER_METER;
	offset_x = b2_centroid.x * PIXEL_PER_METER;
	offset_y = b2_centroid.y * PIXEL_PER_METER;
}

