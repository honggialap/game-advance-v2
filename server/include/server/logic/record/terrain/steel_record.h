#pragma once
#ifndef __STEEL_RECORD_H__
#define __STEEL_RECORD_H__

#include "server/framework/record/record.h"

struct CSteelRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;
	bool is_enable = false;
	bool is_awake = false;

	CSteelRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_visible;
		*packet << is_enable;
		*packet << is_awake;
	}
};
typedef CSteelRecord* pSteelRecord;

#endif // !__STEEL_RECORD_H__
