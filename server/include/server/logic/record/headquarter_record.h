#pragma once
#ifndef __HEADQUARTER_RECORD_H__
#define __HEADQUARTER_RECORD_H__

#include "server/framework/record/record.h"
#include "server/logic/actor/headquarter.h"

struct CHeadquarterRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;

	bool is_enable = false;
	bool is_awake = false;

	EHeadquarterState state = EHeadquarterState::HQ_IDLE;

	CHeadquarterRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		uint8_t send_state = state;
		*packet << send_state;
	}
};
typedef CHeadquarterRecord* pHeadquarterRecord;


#endif // !__HEADQUARTER_RECORD_H__
