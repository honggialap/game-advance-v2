#pragma once
#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CGameServer;
class CLobbyScene
	: public CServerScene
	, public CScene
	, public CTextures
	, public CTextFonts
{
protected:
	CGameServer& game_server;
	CSprites sprites;
	CTexts texts;

	enum class EState {
		WAIT,
		READY
	};
	EState state = EState::WAIT;
	EState GetState() { return state; }
	void SetState(EState new_state) { state = new_state; }

	SceneID play_scene_id = 0;
	float count_down = 0.0f;

public:
	CLobbyScene(CGameServer& game_server);
	~CLobbyScene();
	
	CGameServer& GetGameServer() { return game_server; }

	virtual void Load(std::string data_path) override final;
	virtual void Unload() override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnConnect(ClientID id) override final;
	virtual void OnDisconnect(ClientID id) override final;

	virtual bool ProcessPacket(std::shared_ptr<CPacket> packet) override final;
};

#endif // !__LOBBY_SCENE_H__
