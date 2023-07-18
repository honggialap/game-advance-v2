#pragma once
#ifndef __SAMPLE_ACTOR_H__
#define __SAMPLE_ACTOR_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CSampleActor
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
{
protected:
	CPlayScene& play_scene;

public:
	CSampleActor(CPlayScene& play_scene, std::string name);
	~CSampleActor();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void Unload() override final;

	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void HandleInput(Tick tick) override final;
	virtual void ExecuteCommand(pCommand command) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;

	virtual void HandleEvent(pEvent incomming_event) override final;
};
typedef CSampleActor* pSampleActor;

#endif //!__SAMPLE_ACTOR_H__
