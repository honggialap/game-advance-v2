#pragma once
#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"
#include "bullet.h"

class CPlayScene;
class CPlayerBullet
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CRemoteObject
	, public CUpdatable
	, public CBody
	, public CEventSender
	, public CEventReceiver
	, public CRenderable
	, public CSprites
	, public CPlayerControl
	, public CBullet
{
protected:
	CPlayScene& play_scene;

	int8_t normal_x;
	int8_t normal_y;

	float speed;

public:
	CPlayerBullet(CPlayScene& play_scene, std::string name);
	~CPlayerBullet();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Update(float elapsed_ms) override final;
	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;

	virtual void HandleEvent(pEvent incomming_event) override final;

	virtual void OnShoot(float x, float y, int8_t normal_x, int8_t normal_y) override;
	virtual void OnImpact() override;
};
typedef CPlayerBullet* pPlayerBullet;

#endif //!__PLAYER_BULLET_H__
