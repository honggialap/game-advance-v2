#pragma once
#ifndef __ICE_H__
#define __ICE_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CIce
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CRenderable
	, public CSprites
{
protected:
	CPlayScene& play_scene;

	float position_x = 0.0f;
	float position_y = 0.0f;

public:
	CIce(CPlayScene& play_scene, std::string name);
	~CIce();

	CPlayScene& GetPlayScene() { return play_scene; }

	void GetPosition(float& x, float& y) { x = position_x; y = position_y; }
	void SetPosition(float x, float y) { position_x = x; position_y = y; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;
};
typedef CIce* pIce;

#endif //!__ICE_H__
