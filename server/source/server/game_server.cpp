#include "server/game_server.h"
#include "server/lobby_scene.h"
#include "server/play_scene.h"


void CGameServer::Initialize(std::string data_path) {
	std::ifstream data_file(data_path);
	nlohmann::json data = nlohmann::json::parse(data_file);

	CGame::LoadGameDataFromJson(data);
	CSceneManager::LoadSceneListFromJson(data);
	CServer::LoadServerDataFromJson(data);
	CServer::Initialize();
	CServer::StartListen();
	CPlayerManager::SetMaxPlayerCount(CServer::GetMaxConnectionLimit());
	CPlayerManager::ResetPlayers();

	srand((unsigned)time(NULL));
}

void CGameServer::Shutdown() {
	CServer::StopListen();
	//CServer::DisconnectAll();
	CServer::Shutdown();
}

void CGameServer::PreLoop() {
	LoadScene();
	ProcessNetworks();
}


void CGameServer::Update(float elapsed_ms) {
	ProcessPackets();
	GetCurrentScene()->Update(elapsed_ms);
}

void CGameServer::Render() {
	GetCurrentScene()->Render(GetGameWindow());
}

void CGameServer::PostLoop() {
	UnloadScene();
}

pScene CGameServer::CreateScene(ESceneType type) {
	switch (type) {

	case LOBBY_SCENE:		return new CLobbyScene(*this);
	case PLAY_SCENE:		return new CPlayScene(*this);

	case INVALID_SCENE:
	default: return nullptr;
	}
}

