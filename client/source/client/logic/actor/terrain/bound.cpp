#include "client/logic/actor/terrain/bound.h"
#include "client/play_scene.h"

CBound::CBound(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::BOUND, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene) {
}

CBound::~CBound() {
}

void CBound::LoadFromFile(std::string file_path) {
}

void CBound::Unload() {
}

void CBound::LoadFromPacket(pPacket packet) {
	LoadBodyFromPacket(packet);
}

void CBound::HandleStatePacket(pPacket packet) {
}

void CBound::OnCollisionEnter(CBody* other) {
}

void CBound::OnCollisionExit(CBody* other) {
}
