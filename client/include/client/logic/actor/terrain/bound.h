#pragma once
#ifndef __BOUND_H__
#define __BOUND_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CBound
	: public CClientObject
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

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void OnCollisionEnter(CBody* other) override final;
	virtual void OnCollisionExit(CBody* other) override final;
};
typedef CBound* pBound;

#endif //!__BOUND_H__
