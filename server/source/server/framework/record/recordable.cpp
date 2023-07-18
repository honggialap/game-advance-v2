#include "server/framework/record/recordable.h"
#include "server/framework/record/record_manager.h"

CRecordable::CRecordable(CRecordManager& record_manager, RecordableID id)
	: record_manager(record_manager) 
	, recordable_id(id) {
	record_manager.AddRecordable(this);
}

CRecordable::~CRecordable() {
	record_manager.RemoveRecordable(this);
}

void CRecordable::AssignRecordableID(RecordableID id) {
	if (recordable_id_assigned) return;
	recordable_id_assigned = true;

	recordable_id = id;
	record_manager.AddRecordable(this);
}
