#pragma once
#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "common.h"
#include "engine/framework/network/packet.h"

class CRenderManager;
class CRenderable {
private:
	CRenderManager& render_manager;

	bool is_visible;
	Layer layer;

public:
	CRenderable(CRenderManager& render_manager);
	~CRenderable();

	void LoadRenderableFromJson(json& data);
	void PackRenderableLoadPacket(pPacket packet);
	void LoadRenderableFromPacket(pPacket packet);

	bool IsVisible() { return is_visible; }
	void SetVisible(bool visible);

	Layer GetLayer() { return layer; }
	void SetLayer(Layer value);

	virtual void Render(sf::RenderWindow& window) = 0;
};
typedef CRenderable* pRenderable;

#endif // !__RENDERABLE_H__
