#include "engine/framework/scene/scene_manager.h"

bool CSceneManager::AddSceneData(SceneID id, SceneType type, std::string data_path) {
	if (scenes.find(id) != scenes.end()) return false;

	scenes[id] = std::make_pair(type, data_path);
	return true;
}

bool CSceneManager::RemoveSceneData(SceneID id) {
	if (scenes.find(id) == scenes.end()) return false;
	
	scenes.erase(id);
	return true;
}

void CSceneManager::ClearScenesData() {
	scenes.clear();
}

void CSceneManager::LoadSceneListFromJson(json& data) {
	auto& scenes = data.at("scenes");
	for (auto& scene : scenes.at("scene_list")) {
		SceneID id = scene.at("id");
		ESceneType type = ESceneType(scene.at("type"));
		std::string data_path = scene.at("data_path");
		AddSceneData(id, type, data_path);
	}
	PlayScene(scenes.at("start_scene_id"));
}

void CSceneManager::SetScene(pScene scene) {
	current_scene = scene;
}

bool CSceneManager::PlayScene(SceneID id) {
	if (is_load) return false;
	if (scenes.find(id) == scenes.end()) return false;

	is_load = true;
	next_scene_id = id;
	return true;
}

void CSceneManager::LoadScene() {
	if (!is_load) return;
	is_load = false;

	auto& next_scene = scenes[next_scene_id];
	SceneType scene_type = next_scene.first;
	std::string data_path = next_scene.second;

	auto scene = CreateScene(ESceneType(scene_type));
	if (scene) {
		SetScene(scene);
		scene->Load(data_path);
	}
}

void CSceneManager::UnloadScene() {
	if (!is_load) return;

	current_scene->Unload();
	delete current_scene; current_scene = nullptr;
}
