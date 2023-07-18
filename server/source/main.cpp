#include "server/game_server.h"

int main() {
	CGameServer game_server;
	game_server.Run("data/game_data.json");

	return 0;
}