#pragma once
#ifndef __HEADQUARTER_H__
#define __HEADQUARTER_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

enum EHeadquarterState : uint8_t {
	HQ_IDLE
	, HQ_DESTROYED
};

class CPlayScene;
class CHeadquarter final
	: public CClientObject
	, public CGameObject
	, public CNetworkObject
	, public CBody
	, public CRenderable
	, public CSprites
{
protected:
	CPlayScene& play_scene;
	EHeadquarterState state = EHeadquarterState::HQ_IDLE;

public:
	CHeadquarter(CPlayScene& play_scene, std::string name);
	~CHeadquarter();

	CPlayScene& GetPlayScene() { return play_scene; }

	void SetState(EHeadquarterState new_state) { state = new_state; }
	EHeadquarterState GetState() { return state; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CHeadquarter* pHeadquarter;

#endif //!__HEADQUARTER_H__
