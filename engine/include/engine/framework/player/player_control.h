#pragma once
#ifndef __PLAYER_CONTROL_H__
#define __PLAYER_CONTROL_H__

#include "common.h"

class CPlayerControl {
private:
	PlayerID player_id = 0;

public:
	void SetPlayerID(PlayerID id);
	PlayerID GetPlayerID();

	void ResetPlayer();
};
typedef CPlayerControl* pPlayerControl;


#endif // !__PLAYER_MANAGER_H__
