#pragma once
#ifndef __SAMPLE_ACTOR_H__
#define __SAMPLE_ACTOR_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CPlayScene;
class CSampleActor final
	: public CServerObject
	, public CGameObject
	, public CNetworkObject
	, public CInputHandler
	, public CCommandable
	, public CUpdatable
	, public CBody
	, public CEventSender
	, public CEventReceiver
	, public CRecordable
	, public CRenderable
{
protected:
	CPlayScene& play_scene;

public:
	CSampleActor(CPlayScene& play_scene, std::string name);
	~CSampleActor();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void Load(float position_x, float position_y, json& data) override final;
	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void PackLoadPacket(pPacket packet) override final;

	virtual void HandleInput(Tick tick) override final;
	virtual void ExecuteCommand(pCommand command) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;
	
	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;

	virtual void HandleEvent(pEvent incomming_event) override final;

	virtual pRecord Serialize() override final;
	virtual void Deserialize(pRecord record) override final;
};
typedef CSampleActor* pSampleActor;

#endif //!__SAMPLE_ACTOR_H__
