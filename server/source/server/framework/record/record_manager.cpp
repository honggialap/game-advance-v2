#include "server/framework/record/record_manager.h"

void CRecordManager::AddRecordAtTick(Tick tick, pRecord record){
	auto& records_at_tick = records[tick];
	records_at_tick.push_back(record);
}

std::vector<pRecord>& CRecordManager::GetRecordsAtTick(Tick tick) {
	auto& records_at_tick = records[tick];
	return records_at_tick;
}

void CRecordManager::TrimRecords(Tick from, Tick to) {
	for (auto iterator = records.begin(); iterator != records.end();) {
		if ((*iterator).first < from || (*iterator).first > to) {
			iterator++;
			continue;
		}

		for (auto& record : (*iterator).second) {
			delete record;
			record = nullptr;
		}
		(*iterator).second.clear();

		iterator = records.erase(iterator);
	}
}

void CRecordManager::TrimRecords(Tick before) {
	for (auto iterator = records.begin(); iterator != records.end();) {
		if ((*iterator).first >= before) {
			iterator++;
			continue;
		}

		for (auto& record : (*iterator).second) {
			delete record;
			record = nullptr;
		}
		(*iterator).second.clear();

		iterator = records.erase(iterator);
	}
}

void CRecordManager::ClearRecords() {
	for (auto& records_at_tick : records) {
		for (auto& record : records_at_tick.second) {
			delete record;
			record = nullptr;
		}
		records_at_tick.second.clear();
	}
	records.clear();
}

void CRecordManager::AddRecordable(pRecordable recordable) {
	recordables[recordable->GetRecordableID()] = recordable;
}

void CRecordManager::RemoveRecordable(pRecordable recordable) {
	recordables.erase(recordable->GetRecordableID());
}

void CRecordManager::Serialize(Tick tick) {
	for (auto& recordable_container : recordables) {
		auto& recordable = recordable_container.second;
		AddRecordAtTick(tick, recordable->Serialize());
	}
}

void CRecordManager::Deserialze(Tick tick) {
	for (auto& record : GetRecordsAtTick(tick)) {
		recordables[record->recordable_id]->Deserialize(record);
	}
}
