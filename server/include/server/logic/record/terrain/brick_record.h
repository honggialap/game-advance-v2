#pragma once
#ifndef __BRICK_RECORD_H__
#define __BRICK_RECORD_H__

#include "server/framework/record/record.h"

struct CBrickRecord : public CRecord {
	bool is_active = false;

	CBrickRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
	}
};
typedef CBrickRecord* pBrickRecord;

#endif // !__BRICK_RECORD_H__
