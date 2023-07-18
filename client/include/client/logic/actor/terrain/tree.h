#pragma once
#ifndef __TREE_H__
#define __TREE_H__

#include "engine/framework/framework.h"
#include "client/framework/framework.h"

class CPlayScene;
class CTree
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
	CTree(CPlayScene& play_scene, std::string name);
	~CTree();

	CPlayScene& GetPlayScene() { return play_scene; }

	void GetPosition(float& x, float& y) { x = position_x; y = position_y; }
	void SetPosition(float x, float y) { position_x = x; position_y = y; }

	virtual void LoadFromFile(std::string file_path) override final;
	virtual void Unload() override final;

	virtual void LoadFromPacket(pPacket packet) override final;
	virtual void HandleStatePacket(pPacket packet) override final;

	virtual void Render(sf::RenderWindow& window) override final;
};
typedef CTree* pTree;

#endif //!__TREE_H__
