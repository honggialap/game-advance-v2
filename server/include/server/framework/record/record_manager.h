#pragma once
#ifndef __RECORD_MANAGER_H__
#define __RECORD_MANAGER_H__

#include "recordable.h"

class CRecordManager {
private:
	std::map<Tick, std::vector<pRecord>> records;
	std::map<RecordableID, pRecordable> recordables;

public:
	void AddRecordAtTick(Tick tick, pRecord record);
	std::vector<pRecord>& GetRecordsAtTick(Tick tick);

	void TrimRecords(Tick from, Tick to);
	void TrimRecords(Tick before);
	void ClearRecords();

	void AddRecordable(pRecordable recordable);
	void RemoveRecordable(pRecordable recordable);

	void Serialize(Tick tick);
	void Deserialze(Tick tick);
};

#endif // !__COMMAND_MANAGER_H__
