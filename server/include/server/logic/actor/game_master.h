#pragma once
#ifndef __GAME_MASTER_H__
#define __GAME_MASTER_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

#include "server/logic/actor/tank/player_tank_spawner.h"
#include "server/logic/actor/tank/enemy_tank_spawner.h"
#include "server/logic/actor/pick_up/pick_up_spawner.h"

enum EGameMasterState : uint8_t {
	GM_SET_UP
	, GM_RUN
	, GM_DONE
};

class CPlayScene;
class CGameMaster final
	: public CServerObject
	, public CGameObject
	, public CNetworkObject
	, public CInputHandler
	, public CCommandable
	, public CUpdatable
	, public CEventSender
	, public CEventReceiver
	, public CRecordable
	, public CRenderable
	, public CSprites
	, public CPlayerTankSpawner
	, public CEnemyTankSpawner
	, public CPickUpSpawner
{
protected:
	CPlayScene& play_scene;

	float position_x = 0.0f;
	float position_y = 0.0f;

	EGameMasterState state = GM_SET_UP;

	float spawn_interval = 5000.0f;
	float spawn_interval_counter = 5000.0f;

public:
	CGameMaster(CPlayScene& play_scene, std::string name);
	~CGameMaster();

	CPlayScene& GetPlayScene() { return play_scene; }

	void GetPosition(float& x, float& y) { x = position_x; y = position_y; }
	void SetPosition(float x, float y) { position_x = x; position_y = y; }

	EGameMasterState GetState() { return state; }
	void SetState(EGameMasterState new_state) { state = new_state; }

	virtual void Load(float position_x, float position_y, json& data) override final;
	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void PackLoadPacket(pPacket packet) override final;

	virtual void HandleInput(Tick tick) override final;
	virtual void ExecuteCommand(pCommand command) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void HandleEvent(pEvent incomming_event) override final;

	virtual pRecord Serialize() override final;
	virtual void Deserialize(pRecord record) override final;
};
typedef CGameMaster* pGameMaster;

#endif //!__GAME_MASTER_H__
