#pragma once
#ifndef __ENEMY_TANK_H__
#define __ENEMY_TANK_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CEnemyTank
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CRemoteObject
	, public CUpdatable
	, public CBody
	, public CRenderable
	, public CSprites
{
protected:
	CPlayScene& play_scene;

public:
	CEnemyTank(CPlayScene& play_scene, std::string name);
	~CEnemyTank();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CEnemyTank* pEnemyTank;

#endif //!__ENEMY_TANK_H__
