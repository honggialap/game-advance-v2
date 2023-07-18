#include "engine/framework/render/render_manager.h"

void CRenderManager::AddRenderable(pRenderable renderable) {
	render_listing.push_back(renderable);
	render_dirty_flag = true;
}

void CRenderManager::RemoveRenderable(pRenderable renderable) {
	render_listing.erase(
		std::remove(render_listing.begin(), render_listing.end(), renderable)
		, render_listing.end()
	);
	render_dirty_flag = true;
}

void CRenderManager::MarkRenderDirty() {
	render_dirty_flag = true;
}

void CRenderManager::Render(sf::RenderWindow& window) {
	if (render_dirty_flag) {
		render_dirty_flag = false;

		render_queue.clear();

		for (auto& renderable : render_listing) {
			if (renderable->IsVisible()) render_queue.push_back(renderable);
		}

		std::sort(
			render_queue.begin()
			, render_queue.end()
			, [&](pRenderable a, pRenderable b) {
				return a->GetLayer() > b->GetLayer(); 
			}
		);
	}

	for (auto& renderable : render_queue) {
		renderable->Render(window);
	}
}
