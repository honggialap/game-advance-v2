#pragma once
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CGameServer;
class CPlayScene
	: public CScene
	, public CServerScene
	, public CGameObjectManager
	, public CNetworkObjectManager
	, public CInputManager
	, public CCommandManager
	, public CUpdateManager
	, public CWorld
	, public CEventManager
	, public CRecordManager
	, public CRenderManager
	, public CServerTickCounter
	, public CTextures
{
protected:
	CGameServer& game_server;

	enum class EState{
		LOADING,
		RUN,
		DONE
	};
	EState state = EState::LOADING;
	EState GetState() { return state; }
	void SetState(EState new_state) { state = new_state; }

	SceneID next_play_scene_id = 0;
	SceneID lobby_scene_id = 0;
	float count_down = 0.0f;

public:
	CPlayScene(CGameServer& game_server);
	~CPlayScene();

	CGameServer& GetGameServer() { return game_server; }
	virtual pGameObject CreateGameObject(EActorType actor_type, std::string name) override final;

	virtual void Load(std::string data_path) override final;
	virtual void Unload() override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnConnect(ClientID id) override final;
	virtual void OnDisconnect(ClientID id) override final;

	virtual bool ProcessPacket(std::shared_ptr<CPacket> packet) override final;

	void SendLoadPacket();
	void SendHeadLoadPacket();
	void SendBodyLoadPacket(GameObjectID id);
	void SendEndLoadPacket();

	void SendStartGamePacket();
	void SendStatePacket();
	void SendEndGamePacket();
	void SendStartNextLevelPacket();
	void SendBackToLobbyPacket();

	void HandleLoadDonePacket(pPacket packet);
	void HandleMovePacket(pPacket packet);
	void HandleShootPacket(pPacket packet);
};
typedef CPlayScene* pPlayScene;

#endif // !__PLAY_SCENE_H__
