#pragma once
#ifndef __GAME_SERVER_H__
#define __GAME_SERVER_H__

#include "engine/framework/framework.h"
#include "server/framework/framework.h"

class CGameServer final
	: public CServer
	, public CGame
	, public CSceneManager
	, public CPlayerManager
{
protected:

public:
	virtual void Initialize(std::string data_path) override final;
	virtual void Shutdown() override final;

	virtual void PreLoop() override final;
	virtual void Update(float elapsed_ms) override final;
	virtual void Render() override final;
	virtual void PostLoop() override final;

	virtual pScene CreateScene(ESceneType type) override final;
};


#endif // !__GAME_SERVER_H__
