#pragma once
#ifndef __UPDATABLE_H__
#define __UPDATABLE_H__

#include "common.h"
#include "engine/framework/network/packet.h"

class CUpdateManager;
class CUpdatable {
private:
	CUpdateManager& update_manager;

	bool is_active;

public:
	CUpdatable(CUpdateManager& update_manager);
	~CUpdatable();

	void LoadUpdatableFromJson(json& data);
	void PackUpdatableLoadPacket(pPacket packet);
	void LoadUpdatableFromPacket(pPacket packet);

	bool IsActive() { return is_active; }
	void SetActive(bool active);

	virtual void Update(float elapsed_ms) = 0;
};
typedef CUpdatable* pUpdatable;

#endif // !__UPDATABLE_H__
