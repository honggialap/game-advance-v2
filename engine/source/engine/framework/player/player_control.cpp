#include "engine/framework/player/player_control.h"

void CPlayerControl::SetPlayerID(PlayerID id) {
	player_id = id;
}

PlayerID CPlayerControl::GetPlayerID() {
	return player_id;
}

void CPlayerControl::ResetPlayer() {
	player_id = 0;
}
