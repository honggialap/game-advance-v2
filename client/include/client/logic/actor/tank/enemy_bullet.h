#pragma once
#ifndef __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CEnemyBullet
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CRemoteObject
	, public CBody
	, public CRenderable
	, public CSprites
{
protected:
	CPlayScene& play_scene;

	int8_t normal_x;
	int8_t normal_y;

public:
	CEnemyBullet(CPlayScene& play_scene, std::string name);
	~CEnemyBullet();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CEnemyBullet* pEnemyBullet;

#endif //!__ENEMY_BULLET_H__
