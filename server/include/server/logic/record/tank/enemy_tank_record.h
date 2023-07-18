#pragma once
#ifndef __ENEMY_TANK_RECORD_H__
#define __ENEMY_TANK_RECORD_H__

#include "server/framework/record/record.h"

struct CEnemyTankRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;

	bool is_enable = false;
	bool is_awake = false;

	bool is_spawned = false;

	float position_x = 0.0f;
	float position_y = 0.0f;

	float velocity_x = 0.0f;
	float velocity_y = 0.0f;

	int8_t movement_x = 0;
	int8_t movement_y = 0;

	int8_t normal_x = 0;
	int8_t normal_y = 0;

	CEnemyTankRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_visible;

		*packet << is_enable;
		*packet << is_awake;

		*packet << position_x;
		*packet << position_y;

		*packet << velocity_x;
		*packet << velocity_y;

		*packet << normal_x;
		*packet << normal_y;
	}
};
typedef CEnemyTankRecord* pEnemyTankRecord;

#endif // !__ENEMY_TANK_RECORD_H__
