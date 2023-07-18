#pragma once
#ifndef __RENDER_MANAGER_H__
#define __RENDER_MANAGER_H__

#include "renderable.h"

class CRenderManager {
private:
	std::vector<pRenderable> render_listing;
	std::vector<pRenderable> render_queue;
	bool render_dirty_flag;

public:
	void AddRenderable(pRenderable renderable);
	void RemoveRenderable(pRenderable renderable);

	void MarkRenderDirty();

	void Render(sf::RenderWindow& window);
};
typedef CRenderManager* pRenderManager;

#endif // !__RENDER_MANAGER_H__
