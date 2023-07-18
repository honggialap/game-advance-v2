#pragma once
#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "common.h"

class CTextures {
private:
	std::unordered_map<TextureID, sf::Texture*> textures;

public:
	CTextures();
	virtual ~CTextures();

	void LoadTexturesFromJson(json& data);

	sf::Texture* GetTexture(TextureID id);
	sf::Texture* CreateTexture(TextureID id);
	void DestroyTexture(TextureID id);
	void ClearTextures();
};
typedef CTextures* pTextures;

#endif // !__TEXTURES_H__
