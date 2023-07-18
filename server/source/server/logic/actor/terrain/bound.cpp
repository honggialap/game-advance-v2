#include "server/logic/actor/terrain/bound.h"
#include "server/play_scene.h"

CBound::CBound(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::BOUND, name)
	, CNetworkObject(play_scene)
	, CBody(play_scene) {
	ObtainNetworkID();
}

CBound::~CBound() {
}

void CBound::Load(float position_x, float position_y, json& data) {
	LoadBodyFromJson(data, position_x, position_y);
}

void CBound::LoadFromFile(std::string file_path) {
}

void CBound::Unload() {
}

void CBound::PackLoadPacket(pPacket packet) {
	PackBodyLoadPacket(packet);
}

void CBound::OnCollisionEnter(CBody* other) {
}

void CBound::OnCollisionExit(CBody* other) {
}

