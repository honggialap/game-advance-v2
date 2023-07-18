#pragma once
#ifndef __WATER_H__
#define __WATER_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CWater
	: public CClientObject
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

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CWater* pWater;

#endif //!__WATER_H__
