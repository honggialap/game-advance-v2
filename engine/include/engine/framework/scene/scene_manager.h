#pragma once
#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "scene.h"

class CSceneManager {
private:
	std::map<SceneID, std::pair<SceneType, std::string>> scenes;
	pScene current_scene = nullptr;

	bool is_load = false;
	SceneID next_scene_id = 0;

public:
	bool AddSceneData(SceneID id, SceneType type, std::string dapa_path);
	bool RemoveSceneData(SceneID id);
	void ClearScenesData();

	void LoadSceneListFromJson(json& data);

	pScene GetCurrentScene() { return current_scene; }
	void SetScene(pScene scene);
	
	bool PlayScene(SceneID id);
	void LoadScene();
	void UnloadScene();
	
	virtual pScene CreateScene(ESceneType scene_type) = 0;
};
typedef CSceneManager* pSceneManager;

#endif // !__SCENE_MANAGER_H__