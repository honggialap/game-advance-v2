#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__

#include "common.h"

class CSceneManager;
class CScene {
private:
	CSceneManager& scene_manager;

public:
	CScene(CSceneManager& scene_manager);
	virtual ~CScene() = 0;

	CSceneManager& GetSceneManager() { return scene_manager; }

	virtual void Update(float elapsed_ms) = 0;
	virtual void Render(sf::RenderWindow& window) = 0;

	virtual void Load(std::string data_path) = 0;
	virtual void Unload() = 0;
};
typedef CScene* pScene;

#endif // !__SCENE_H__





