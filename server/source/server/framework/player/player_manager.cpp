#include "server/framework/player/player_manager.h"

void CPlayerManager::PlayerConfirm(PlayerID player_id, ClientID client_id) {
	players[player_id].first = client_id;
}

void CPlayerManager::PlayerReady(PlayerID player_id) {
	players[player_id].second = true;
}

PlayerID CPlayerManager::GetNextAvailablePlayerID() {
	PlayerID available_id = 0;

	for (auto& player : players) {
		if (!player.second.second) {
			available_id = player.first;
			break;
		}
	}

	return available_id;
}

ClientID CPlayerManager::GetPlayer(PlayerID player_id) {
	return players[player_id].first;
}

PlayerID CPlayerManager::GetMaxPlayerCount() {
	return max_player_count;
}

void CPlayerManager::SetMaxPlayerCount(PlayerID value) {
	max_player_count = value;
}

bool CPlayerManager::AllPlayersReady() {
	bool result = true;

	for (auto& player : players) {
		if (!player.second.second) {
			result = false;
			break;
		}
	}

	return result;
}

void CPlayerManager::ResetPlayerReadyStatus() {
	for (auto& player : players) {
		player.second.second = false;
	}
}

void CPlayerManager::ResetPlayers() {
	players.clear();

	for (PlayerID id = 1; id <= max_player_count; id++) {
		players[id] = std::make_pair(0, false);
	}

}
