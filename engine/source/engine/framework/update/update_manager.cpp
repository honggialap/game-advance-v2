#include "engine/framework/update/update_manager.h"

void CUpdateManager::AddUpdatable(pUpdatable updatable) {
	update_listing.push_back(updatable);
	update_dirty_flag = true;
}

void CUpdateManager::RemoveUpdatable(pUpdatable updatable) {
	update_listing.erase(
		std::remove(update_listing.begin(), update_listing.end(), updatable)
		, update_listing.end()
	);
	update_dirty_flag = true;
}

void CUpdateManager::MarkUpdateDirty() {
	update_dirty_flag = true;
}

void CUpdateManager::Update(float elapsed_ms) {
	if (update_dirty_flag) {
		update_dirty_flag = false;

		update_queue.clear();

		for (auto& updatable : update_listing) {
			if (updatable->IsActive()) update_queue.push_back(updatable);
		}
	}

	for (auto& updatable : update_queue) {
		updatable->Update(elapsed_ms);
	}
}
