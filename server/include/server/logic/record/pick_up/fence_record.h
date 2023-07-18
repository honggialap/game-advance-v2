#pragma once
#ifndef __FENCE_RECORD_H__
#define __FENCE_RECORD_H__

#include "server/framework/record/record.h"

struct CFenceRecord : public CRecord {
	bool is_active = false;
	float position_x = 0.0f;
	float position_y = 0.0f;

	CFenceRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
		*packet << position_x;
		*packet << position_y;
	}
};
typedef CFenceRecord* pFenceRecord;


#endif // !__FENCE_RECORD_H__
