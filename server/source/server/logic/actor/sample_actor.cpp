#include "server/logic/actor/sample_actor.h"
#include "server/play_scene.h"

CSampleActor::CSampleActor(CPlayScene& play_scene, std::string name)
	: play_scene(play_scene)
	, CServerObject(play_scene)
	, CGameObject(play_scene, EActorType::INVALID_ACTOR, name)
	, CNetworkObject(play_scene)
	, CInputHandler(play_scene)
	, CCommandable(play_scene, GetID())
	, CUpdatable(play_scene)
	, CBody(play_scene)
	, CEventSender(play_scene)
	, CEventReceiver(play_scene)
	, CRecordable(play_scene, GetID())
	, CRenderable(play_scene) {
	SubcribeEvent(EEventType::INVALID_EVENT);
	ObtainNetworkID();
}

CSampleActor::~CSampleActor() {
}

void CSampleActor::Load(float position_x, float position_y, json& data) {
}

void CSampleActor::LoadFromFile(std::string file_path) {
}

void CSampleActor::Unload() {
}

void CSampleActor::PackLoadPacket(pPacket packet) {
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

pRecord CSampleActor::Serialize() {
	return pRecord();
}

void CSampleActor::Deserialize(pRecord record) {
}
