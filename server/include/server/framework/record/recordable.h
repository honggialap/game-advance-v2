#pragma once
#ifndef __RECORDABLE_H__
#define __RECORDABLE_H__

#include "record.h"

class CRecordManager;
class CRecordable {
private:
	CRecordManager& record_manager;
	RecordableID recordable_id = INVALID_GAMEOBJECT_ID;
	bool recordable_id_assigned = false;

public:
	CRecordable(CRecordManager& record_manager, RecordableID id);
	~CRecordable();

	RecordableID GetRecordableID() { return recordable_id; }
	void AssignRecordableID(RecordableID id);

	virtual pRecord Serialize() = 0;
	virtual void Deserialize(pRecord record) = 0;
};
typedef CRecordable* pRecordable;

#endif // !__RECORDABLE_H__
