#include "engine/framework/scene/scene.h"
#include "engine/framework/scene/scene_manager.h"

CScene::CScene(CSceneManager& scene_manager) 
	: scene_manager(scene_manager) {
}

CScene::~CScene() {
}
