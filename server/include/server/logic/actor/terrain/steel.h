#pragma once
#ifndef __STEEL_H__
#define __STEEL_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CPlayScene;
class CFenceSpawner;
class CSteel
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
{
protected:
	CPlayScene& play_scene;

	CFenceSpawner* fence_spawner = nullptr;
	bool is_spawned = false;

public:
	CSteel(CPlayScene& play_scene, std::string name);
	~CSteel();

	CPlayScene& GetPlayScene() { return play_scene; }

	void SetFenceSpawner(CFenceSpawner* spawner);
	bool IsSpawned() { return is_spawned; }

	void Spawn();
	void Despawn();

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
typedef CSteel* pSteel;

#endif //!__STEEL_H__
