#include "server/framework/network/server_scene.h"
#include "server/framework/network/server.h"

CServerScene::CServerScene(CServer& server)
	: server(server) {
	server.SetServerScene(this);
}

CServerScene::~CServerScene() {
	server.DropServerScene(this);
}
