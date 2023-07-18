#pragma once
#ifndef __GAME_CLIENT_H__
#define __GAME_CLIENT_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CGameClient final
	: public CClient
	, public CGame
	, public CSceneManager
	, public CPlayerControl
{
protected:

public:
	virtual void Initialize(std::string data_path) final;
	virtual void Shutdown() final;

	virtual void PreLoop() final;
	virtual void Update(float elapsed_ms) final;
	virtual void Render() final;
	virtual void PostLoop() final;

	virtual pScene CreateScene(ESceneType type) final;
};

#endif // !__GAME_CLIENT_H__
