#pragma once
#ifndef __ENEMY_TANK_H__
#define __ENEMY_TANK_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

#include "tank.h"
#include "enemy_tank_spawnable.h"

class CPlayScene;
class CEnemyTankSpawner;
class CEnemyTank
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
	, public CSprites
	, public CTank
	, public CEnemyTankSpawnable
{
protected:
	CPlayScene& play_scene;

	int8_t normal_x = 0;
	int8_t normal_y = -1;

	int8_t movement_x = 0;
	int8_t movement_y = 0;

	float speed = 0.1f;

public:
	CEnemyTank(CPlayScene& play_scene, std::string name);
	~CEnemyTank();

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

	virtual void OnSpawn(float x, float y) override final;
	virtual void OnDespawn() override final;
};
typedef CEnemyTank* pEnemyTank;

#endif //!__ENEMY_TANK_H__
