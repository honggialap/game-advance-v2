#pragma once
#ifndef __PLAYER_BULLET_RECORD_H__
#define __PLAYER_BULLET_RECORD_H__

#include "server/framework/record/record.h"

struct CPlayerBulletRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;

	bool is_enable = false;
	bool is_awake = false;

	bool is_shot = false;

	float position_x = 0.0f;
	float position_y = 0.0f;

	float velocity_x = 0.0f;
	float velocity_y = 0.0f;

	int8_t movement_x = 0;
	int8_t movement_y = 0;

	int8_t normal_x = 0;
	int8_t normal_y = 0;

	CPlayerBulletRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
		*packet << is_visible;

		*packet << is_enable;
		*packet << is_awake;

		*packet << is_shot;

		*packet << position_x;
		*packet << position_y;

		*packet << velocity_x;
		*packet << velocity_y;

		*packet << normal_x;
		*packet << normal_y;
	}
};
typedef CPlayerBulletRecord* pPlayerBulletRecord;

#endif // !__PLAYER_BULLET_RECORD_H__
