#include "engine/framework/render/renderable.h"
#include "engine/framework/render/render_manager.h"

CRenderable::CRenderable(CRenderManager& render_manager)
	: render_manager(render_manager)
	, is_visible(false)
	, layer(Layer(0)) {
	render_manager.AddRenderable(this);
}

CRenderable::~CRenderable() {
	render_manager.RemoveRenderable(this);
}

void CRenderable::LoadRenderableFromJson(json& data) {
	if (!data.contains("visible")) return;
	bool is_visible = data.at("visible");
	SetVisible(is_visible);

	if (!data.contains("layer")) return;
	Layer layer = data.at("layer");
	SetLayer(layer);
}

void CRenderable::PackRenderableLoadPacket(pPacket packet) {
	bool is_visible = IsVisible();
	*packet << is_visible;

	Layer layer = GetLayer();
	*packet << layer;
}

void CRenderable::LoadRenderableFromPacket(pPacket packet) {
	bool is_visible;
	*packet >> is_visible;
	SetVisible(is_visible);

	Layer layer;
	*packet >> layer;
	SetLayer(layer);
}

void CRenderable::SetVisible(bool visible) {
	is_visible = visible;
	render_manager.MarkRenderDirty();
}

void CRenderable::SetLayer(Layer value) {
	layer = value;
	render_manager.MarkRenderDirty();
}