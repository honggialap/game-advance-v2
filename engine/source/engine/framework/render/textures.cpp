#include "engine/framework/render/textures.h"

CTextures::CTextures() {
}

CTextures::~CTextures() {
	ClearTextures();
}

void CTextures::LoadTexturesFromJson(json& data) {
	if (!data.contains("textures")) return;

	for (auto& texture_data : data.at("textures")) {
		TextureID id = texture_data.at("id");
		auto texture = CreateTexture(id);
		
		std::string file_path = texture_data.at("file_path");
		texture->loadFromFile(file_path);
	}
}

sf::Texture* CTextures::GetTexture(TextureID id) {
	if (textures.find(id) == textures.end()) throw;
	return textures.at(id);
}

sf::Texture* CTextures::CreateTexture(TextureID id) {
	if (textures.find(id) != textures.end()) throw;

	auto texture = new sf::Texture();
	textures.insert(std::make_pair(id, texture));

	return texture;
}

void CTextures::DestroyTexture(TextureID id) {
	if (textures.find(id) == textures.end()) throw;

	auto texture = textures.at(id);
	delete texture; texture = nullptr;

	textures.erase(id);
}

void CTextures::ClearTextures() {
	for (auto& texture_container : textures) {
		auto texture = texture_container.second;
		delete texture; texture = nullptr;
	}
	textures.clear();
}
