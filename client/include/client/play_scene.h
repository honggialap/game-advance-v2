#pragma once
#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CGameClient;
class CPlayScene
	: public CScene
	, public CClientScene
	, public CGameObjectManager
	, public CNetworkObjectManager
	, public CInputManager
	, public CCommandManager
	, public CUpdateManager
	, public CWorld
	, public CEventManager
	, public CRenderManager
	, public CClientTickCounter
	, public CTextures
{
protected:
	CGameClient& game_client;

	enum class EState {
		LOADING,
		RUN,
		DONE
	};
	EState state = EState::LOADING;
	EState GetState() { return state; }
	void SetState(EState new_state) { state = new_state; }

	SceneID play_scene_id = 2;
	SceneID lobby_scene_id = 1;

public:
	CPlayScene(CGameClient& game_client);
	~CPlayScene();

	CGameClient& GetGameClient() { return game_client; }
	virtual pGameObject CreateGameObject(EActorType actor_type, std::string name) final;

	virtual void Load(std::string data_path) final;
	virtual void Unload() final;

	virtual void Update(float elapsed_ms) final;
	virtual void Render(sf::RenderWindow& window) final;

	virtual void OnConnect() final;
	virtual void OnDisconnect() final;
	virtual void OnConnectFail() final;

	virtual bool ProcessPacket(std::shared_ptr<CPacket> packet) final;

	void HandleHeadLoadPacket(pPacket packet);
	void HandleBodyLoadPacket(pPacket packet);
	void HandleEndLoadPacket(pPacket packet);
	void SendLoadDonePacket();

	void SendMovePacket(pCommand command);
	void SendShootPacket(pCommand command);

	void HandleStartGamePacket(pPacket packet);
	void HandleStatePacket(pPacket packet);
	void HandleEndGamePacket(pPacket packet);
};
typedef CPlayScene* pPlayScene;

#endif // !__PLAY_SCENE_H__
