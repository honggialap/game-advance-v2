#include "engine/framework/render/sprites.h"

CSprites::CSprites(CTextures& textures)
	: textures(textures) {
}

CSprites::~CSprites() {
	ClearSprites();
}

void CSprites::LoadSpritesFromJson(json& data) {
	if (!data.contains("sprites")) return;

	for (auto& sprite_data : data.at("sprites")) {
		SpriteID id = sprite_data.at("id");
		auto sprite = CreateSprite(id);

		TextureID texture_id = sprite_data.at("texture_id");
		auto texture = textures.GetTexture(texture_id);
		sprite->setTexture(*texture);

		int left = sprite_data.at("left");
		int top = sprite_data.at("top");
		int width = sprite_data.at("width");
		int height = sprite_data.at("height");

		sprite->setTextureRect(
			sf::IntRect(left, top, width, height)
		);

		int offset_x = sprite_data.at("offset_x");
		int offset_y = sprite_data.at("offset_y");
		float origin_x = (width / 2.0f) + offset_x;
		float origin_y = (height / 2.0f) - offset_y;

		sprite->setOrigin(origin_x, origin_y);
	}
}

sf::Sprite* CSprites::GetSprite(SpriteID id) {
	if (sprites.find(id) == sprites.end()) throw;
	return sprites.at(id);
}

sf::Sprite* CSprites::CreateSprite(SpriteID id) {
	if (sprites.find(id) != sprites.end()) throw;

	auto sprite = new sf::Sprite();
	sprites.insert(std::make_pair(id, sprite));

	return sprite;
}

void CSprites::DestroySprite(SpriteID id) {
	if (sprites.find(id) == sprites.end()) throw;
	
	auto sprite = sprites.at(id);
	delete sprite; sprite = nullptr;

	sprites.erase(id);
}

void CSprites::ClearSprites() {
	for (auto& sprite_container : sprites) {
		auto sprite = sprite_container.second;
		delete sprite; sprite = nullptr;
	}
	sprites.clear();
}
