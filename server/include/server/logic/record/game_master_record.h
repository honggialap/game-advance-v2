#pragma once
#ifndef __GAME_MASTER_RECORD_H__
#define __GAME_MASTER_RECORD_H__

#include "server/framework/record/record.h"
#include "server/logic/actor/game_master.h"

struct CGameMasterRecord : public CRecord {
	bool is_active = false;
	bool is_visible = false;

	EGameMasterState state = EGameMasterState::GM_SET_UP;
	float spawn_interval_coutner = 0;

	CGameMasterRecord(RecordableID id, NetworkID network_object_id)
		: CRecord(id, network_object_id) {}

	virtual void Pack(pPacket packet) override final {
		// so sad, i got nothing to send :(
	}
};
typedef CGameMasterRecord* pGameMasterRecord;

#endif // !__GAME_MASTER_RECORD_H__
