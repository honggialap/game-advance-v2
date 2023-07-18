#include "client/game_client.h"
#include "client/lobby_scene.h"
#include "client/play_scene.h"

void CGameClient::Initialize(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	CGame::LoadGameDataFromJson(data);
	CSceneManager::LoadSceneListFromJson(data);
	CClient::LoadClientDataFromJson(data);
	CClient::Initialize();
	CPlayerControl::ResetPlayer();
}

void CGameClient::Shutdown() {
	CClient::Disconnect();
	CClient::Shutdown();
}

void CGameClient::PreLoop() {
	LoadScene();
	if (IsConnecting()) ProcessNetworks();
}

void CGameClient::Update(float elapsed_ms) {
	if (IsConnecting()) ProcessPackets();
	GetCurrentScene()->Update(elapsed_ms);
}

void CGameClient::Render() {
	GetCurrentScene()->Render(GetGameWindow());
}

void CGameClient::PostLoop() {
	UnloadScene();
}

pScene CGameClient::CreateScene(ESceneType type) {
	switch (type) {

	case LOBBY_SCENE:		return new CLobbyScene(*this);
	case PLAY_SCENE:		return new CPlayScene(*this);

	case INVALID_SCENE:
	default: return nullptr;
	}
}

