#pragma once
#ifndef __PLAYER_TANK_RECORD_H__
#define __PLAYER_TANK_RECORD_H__

#include "server/framework/record/record.h"

struct CPlayerTankRecord : public CRecord {
	bool is_active = false;
	float position_x = 0.0f;
	float position_y = 0.0f;
	float velocity_x = 0.0f;
	float velocity_y = 0.0f;
	int8_t normal_x = 0;
	int8_t normal_y = 0;

	CPlayerTankRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
		*packet << position_x;
		*packet << position_y;
		*packet << velocity_x;
		*packet << velocity_y;
		*packet << normal_x;
		*packet << normal_y;
	}
};
typedef CPlayerTankRecord* pPlayerTankRecord;

#endif // !__PLAYER_TANK_RECORD_H__
