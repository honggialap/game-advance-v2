#include "client/logic/actor/sample_actor.h"
#include "client/play_scene.h"

CSampleActor::CSampleActor(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CClientObject(play_scene)
	, CGameObject(play_scene, EActorType::INVALID_ACTOR, name)
	, CNetworkObject(play_scene)
	, CInputHandler(play_scene)
	, CCommandable(play_scene, GetID())
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRenderable(play_scene) {
	SubcribeEvent(EEventType::INVALID_EVENT);
}

CSampleActor::~CSampleActor() {
}

void CSampleActor::LoadFromFile(std::string file_path) {
}

void CSampleActor::LoadFromPacket(pPacket packet) {
}

void CSampleActor::Unload() {
}

void CSampleActor::HandleStatePacket(pPacket packet) {
}

void CSampleActor::HandleInput(Tick tick) {
}

void CSampleActor::ExecuteCommand(pCommand command) {
}

void CSampleActor::Update(float elapsed_ms) {
}

void CSampleActor::Render(sf::RenderWindow& window) {
}

void CSampleActor::OnCollisionEnter(CBody* other) {
}

void CSampleActor::OnCollisionExit(CBody* other) {
}

void CSampleActor::HandleEvent(pEvent incomming_event) {
}
