#pragma once
#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CGameClient;
class CLobbyScene
	: public CClientScene
	, public CScene
	, public CTextures
	, public CTextFonts
{
protected:
	CGameClient& game_client;
	CSprites sprites;
	CTexts texts;
	SceneID play_scene_id = 0;

	enum class EState {
		CONNECTING,
		WAIT,
	};
	EState state = EState::CONNECTING;
	EState GetState() { return state; }
	void SetState(EState new_state) { state = new_state; }

public:
	CLobbyScene(CGameClient& game_client);
	~CLobbyScene();

	CGameClient& GetGameClient() { return game_client; }

	virtual void Load(std::string data_path) final;
	virtual void Unload() final;

	virtual void Update(float elapsed_ms) final;
	virtual void Render(sf::RenderWindow& window) final;

	virtual void OnConnect() final;
	virtual void OnDisconnect() final;
	virtual void OnConnectFail() final;

	virtual bool ProcessPacket(std::shared_ptr<CPacket> packet) final;
};

#endif // !__LOBBY_SCENE_H__
