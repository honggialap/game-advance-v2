#include "engine/framework/update/updatable.h"
#include "engine/framework/update/update_manager.h"

CUpdatable::CUpdatable(CUpdateManager& update_manager)
	: update_manager(update_manager)
	, is_active(false)	{
	update_manager.AddUpdatable(this);
}

CUpdatable::~CUpdatable() {
	update_manager.RemoveUpdatable(this);
}

void CUpdatable::LoadUpdatableFromJson(json& data) {
	if (!data.contains("active")) return;
	is_active = data.at("active");
}

void CUpdatable::PackUpdatableLoadPacket(pPacket packet) {
	bool is_active = IsActive();
	*packet << is_active;
}

void CUpdatable::LoadUpdatableFromPacket(pPacket packet) {
	bool is_active;
	*packet >> is_active;
	SetActive(is_active);
}

void CUpdatable::SetActive(bool active) {
	is_active = active;
	update_manager.MarkUpdateDirty();
}
