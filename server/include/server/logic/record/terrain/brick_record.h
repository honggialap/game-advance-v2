#pragma once
#ifndef __BRICK_RECORD_H__
#define __BRICK_RECORD_H__

#include "server/framework/record/record.h"
#include "server/logic/actor/terrain/brick.h"

struct CBrickRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;
	bool is_enable = false;
	bool is_awake = false;

	CBrickRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_visible;
		*packet << is_enable;
		*packet << is_awake;
	}
};
typedef CBrickRecord* pBrickRecord;

#endif // !__BRICK_RECORD_H__
