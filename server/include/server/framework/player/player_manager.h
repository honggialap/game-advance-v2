#pragma once
#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__

#include "engine/framework/framework.h"

class CPlayerManager {
private:
	std::map<PlayerID, std::pair<ClientID, bool>> players;
	PlayerID max_player_count;

public:
	void PlayerConfirm(PlayerID player_id, ClientID client_id);
	void PlayerReady(PlayerID player_id);

	PlayerID GetNextAvailablePlayerID();
	ClientID GetPlayer(PlayerID player_id);

	PlayerID GetMaxPlayerCount();
	void SetMaxPlayerCount(PlayerID value);
	
	bool AllPlayersReady();
	void ResetPlayerReadyStatus();

	void ResetPlayers();
};
typedef CPlayerManager* pPlayerManager;

#endif // !__PLAYER_MANAGER_H__
