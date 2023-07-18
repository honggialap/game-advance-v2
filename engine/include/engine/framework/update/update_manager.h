#pragma once
#ifndef __UPDATE_MANAGER_H__
#define __UPDATE_MANAGER_H__

#include "updatable.h"

class CUpdateManager {
private:
	std::vector<pUpdatable> update_listing;
	std::vector<pUpdatable> update_queue;
	bool update_dirty_flag;

public:
	void AddUpdatable(pUpdatable updatable);
	void RemoveUpdatable(pUpdatable updatable);

	void MarkUpdateDirty();

	void Update(float elapsed_ms);
};
typedef CUpdateManager* pUpdateManager;

#endif // !__UPDATE_MANAGER_H__
