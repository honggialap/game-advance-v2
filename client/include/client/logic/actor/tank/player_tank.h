#pragma once
#ifndef __PLAYER_TANK_H__
#define __PLAYER_TANK_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

#include "tank.h"

class CPlayScene;
class CPlayerTank
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CRemoteObject
	, public CInputHandler
	, public CCommandable
	, public CUpdatable
	, public CBody
	, public CEventSender
	, public CEventReceiver
	, public CRenderable
	, public CSprites
	, public CPlayerControl
	, public CTank
{
protected:
	CPlayScene& play_scene;

	int8_t normal_x;
	int8_t normal_y;

	int8_t movement_x;
	int8_t movement_y;

	float speed;

public:
	CPlayerTank(CPlayScene& play_scene, std::string name);
	~CPlayerTank();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void HandleInput(Tick tick) override final;
	virtual void ExecuteCommand(pCommand command) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;

	virtual void HandleEvent(pEvent incomming_event) override final;
};
typedef CPlayerTank* pPlayerTank;

#endif //!__PLAYER_TANK_H__
