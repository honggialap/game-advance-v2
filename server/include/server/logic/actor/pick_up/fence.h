#pragma once
#ifndef __FENCE_H__
#define __FENCE_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

#include "pick_up_spawnable.h"

class CPlayScene;
class CFence
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
	, public CPickUpSpawnable
{
protected:
	CPlayScene& play_scene;

public:
	CFence(CPlayScene& play_scene, std::string name);
	~CFence();

	CPlayScene& GetPlayScene() { return play_scene; }

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

	virtual void OnSpawn(float x, float y) override final;
	virtual void OnDespawn() override final;
};
typedef CFence* pFence;

#endif // !__FENCE_H__
