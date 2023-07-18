#pragma once
#ifndef __GAME_MASTER_RECORD_H__
#define __GAME_MASTER_RECORD_H__

#include "server/framework/record/record.h"

struct CGameMasterRecord : public CRecord {
	bool is_active = false;
	float spawn_interval = 0;

	CGameMasterRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		*packet << is_active;
	}
};
typedef CGameMasterRecord* pGameMasterRecord;


#endif // !__GAME_MASTER_RECORD_H__
