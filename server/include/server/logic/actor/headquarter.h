#pragma once
#ifndef __HEADQUARTER_H__
#define __HEADQUARTER_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

#include "terrain/fence_spawner.h"

enum EHeadquarterState : uint8_t {
	HQ_IDLE
	, HQ_DESTROYED
};

class CPlayScene;
class CHeadquarter final
	: public CServerObject
	, public CGameObject
	, public CNetworkObject
	, public CUpdatable
	, public CBody
	, public CEventSender
	, public CEventReceiver
	, public CRecordable
	, public CRenderable
	, public CSprites
	, public CFenceSpawner
{
protected:
	CPlayScene& play_scene;

	EHeadquarterState state = HQ_IDLE;

public:
	CHeadquarter(CPlayScene& play_scene, std::string name);
	~CHeadquarter();

	CPlayScene& GetPlayScene() { return play_scene; }

	EHeadquarterState GetState() { return state; }
	void SetState(EHeadquarterState new_state) { state = new_state; }

	virtual void Load(float position_x, float position_y, json& data) override final;
	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void PackLoadPacket(pPacket packet) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;

	virtual void HandleEvent(pEvent incomming_event) override final;

	virtual pRecord Serialize() override final;
	virtual void Deserialize(pRecord record) override final;
};
typedef CHeadquarter* pHeadquarter;

#endif //!__HEADQUARTER_H__
