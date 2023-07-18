#pragma once
#ifndef __WATER_H__
#define __WATER_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CPlayScene;
class CWater
	: public CServerObject
	, public CGameObject
	, public CNetworkObject
	, public CBody
	, public CRenderable
	, public CSprites
{
protected:
	CPlayScene& play_scene;

public:
	CWater(CPlayScene& play_scene, std::string name);
	~CWater();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void Load(float position_x, float position_y, json& data) override final;
	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void PackLoadPacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CWater* pWater;

#endif //!__WATER_H__
