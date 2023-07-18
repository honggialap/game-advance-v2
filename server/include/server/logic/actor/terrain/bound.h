#pragma once
#ifndef __BOUND_H__
#define __BOUND_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CPlayScene;
class CBound final
	: public CServerObject
	, public CGameObject
	, public CNetworkObject
	, public CBody
{
protected:
	CPlayScene& play_scene;

public:
	CBound(CPlayScene& play_scene, std::string name);
	~CBound();

	CPlayScene& GetPlayScene() { return play_scene; }

	virtual void Load(float position_x, float position_y, json& data) override final;
	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void PackLoadPacket(pPacket packet) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CBound* pBound;
		
#endif //!__BOUND_H__
