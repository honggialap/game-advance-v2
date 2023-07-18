#pragma once
#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"
#include "bullet.h"

class CPlayScene;
class CPlayerTank;
class CPlayerBullet
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

	virtual void OnShoot(float x, float y, int8_t nx, int8_t ny) override final;
	virtual void OnImpact() override final;

};
typedef CPlayerBullet* pPlayerBullet;

#endif //!__PLAYER_BULLET_H__
