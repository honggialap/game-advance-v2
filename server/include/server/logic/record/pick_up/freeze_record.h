#pragma once
#ifndef __FREEZE_RECORD_H__
#define __FREEZE_RECORD_H__

#include "server/framework/record/record.h"

struct CFreezeRecord : public CRecord {
	bool is_active = false;
	float position_x = 0.0f;
	float position_y = 0.0f;

	CFreezeRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
		*packet << position_x;
		*packet << position_y;
	}
};
typedef CFreezeRecord* pFreezeRecord;


#endif // !__FREEZE_RECORD_H__
