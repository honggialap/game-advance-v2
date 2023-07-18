#pragma once
#ifndef __BOMB_RECORD_H__
#define __BOMB_RECORD_H__

#include "server/framework/record/record.h"

struct CBombRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;

	bool is_enable = false;
	bool is_awake = false;

	bool is_spawned = false;

	float position_x = 0.0f;
	float position_y = 0.0f;

	CBombRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_visible;

		*packet << is_enable;
		*packet << is_awake;

		*packet << position_x;
		*packet << position_y;
	}
};
typedef CBombRecord* pBombRecord;

#endif // !__BOMB_RECORD_H__
