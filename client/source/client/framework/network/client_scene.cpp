#include "client/framework/network/client_scene.h"
#include "client/framework/network/client.h"

CClientScene::CClientScene(CClient& client)
	: client(client) {
	client.SetClientScene(this);
}

CClientScene::~CClientScene() {
	client.DropClientScene(this);
}
