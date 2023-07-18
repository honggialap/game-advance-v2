#pragma once
#ifndef __RECORD_H__
#define __RECORD_H__

#include "engine/framework/framework.h"

struct CRecord
{
public:
	RecordableID recordable_id = INVALID_GAMEOBJECT_ID;
	NetworkID network_object_id = INVALID_GAMEOBJECT_ID;

public:
	CRecord(RecordableID id, NetworkID network_object_id)
		: recordable_id(id)
		, network_object_id(network_object_id)
	{}
	virtual ~CRecord() = 0 {}
	virtual void Pack(pPacket packet) = 0;
};
typedef CRecord* pRecord;

#endif // !__RECORD_H__
