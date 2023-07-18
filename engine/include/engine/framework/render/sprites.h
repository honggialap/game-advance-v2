#pragma once
#ifndef __SPRITES_H__
#define __SPRITES_H__

#include "common.h"
#include "textures.h"

class CSprites {
private:
	CTextures& textures;

	std::unordered_map<SpriteID, sf::Sprite*> sprites;

public:
	CSprites(CTextures& textures);
	virtual ~CSprites();

	void LoadSpritesFromJson(json& data);

	CTextures& GetTextures() { return textures; }

	sf::Sprite* GetSprite(SpriteID id);
	sf::Sprite* CreateSprite(SpriteID id);
	void DestroySprite(SpriteID id);
	void ClearSprites();
};
typedef CSprites* pSprites;

#endif // !__SPRITES_H__
