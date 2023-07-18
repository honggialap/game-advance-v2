#pragma once
#ifndef __HEADQUARTER_RECORD_H__
#define __HEADQUARTER_RECORD_H__

#include "server/framework/record/record.h"

struct CHeadquarterRecord : public CRecord {
	bool is_active = false;
	
	CHeadquarterRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
	}
};
typedef CHeadquarterRecord* pHeadquarterRecord;


#endif // !__HEADQUARTER_RECORD_H__
