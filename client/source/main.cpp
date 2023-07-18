#include "client/game_client.h"

int main() {
	CGameClient game_client;
	game_client.Run("data/game_data.json");

	return 0;
}