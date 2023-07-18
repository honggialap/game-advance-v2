#pragma once
#ifndef __GAME_MASTER_H__
#define __GAME_MASTER_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CGameMaster
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CRemoteObject
	, public CRenderable
	, public CSprites
{
protected:
	CPlayScene& play_scene;

	float position_x = 0.0f;
	float position_y = 0.0f;

public:
	CGameMaster(CPlayScene& play_scene, std::string name);
	~CGameMaster();

	CPlayScene& GetPlayScene() { return play_scene; }

	void GetPosition(float& x, float& y) { x = position_x; y = position_y; }
	void SetPosition(float x, float y) { position_x = x; position_y = y; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;
};
typedef CGameMaster* pGameMaster;

#endif //!__GAME_MASTER_H__
