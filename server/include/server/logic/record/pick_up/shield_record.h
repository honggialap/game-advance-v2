#pragma once
#ifndef __SHIELD_RECORD_H__
#define __SHIELD_RECORD_H__

#include "server/framework/record/record.h"
#include "server/logic/actor/pick_up/shield.h"

struct CShieldRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;

	bool is_enable = false;
	bool is_awake = false;

	bool is_spawned = false;

	float position_x = 0.0f;
	float position_y = 0.0f;

	CShieldRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_visible;

		*packet << is_enable;
		*packet << is_awake;

		*packet << position_x;
		*packet << position_y;
	}
};
typedef CShieldRecord* pShieldRecord;


#endif // !__SHIELD_RECORD_H__
