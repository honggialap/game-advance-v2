#include "engine/framework/audio/musics.h"

CMusics::CMusics() {
}

CMusics::~CMusics() {
	ClearMusics();
}

void CMusics::LoadMusicsFromJson(json& data) {
	if (!data.contains("musics")) return;

	for (auto& music_data : data.at("musics")) {
		MusicID id = music_data.at("id");
		std::string file_path = music_data.at("file_path");
		CreateMusic(id, file_path);
	}
}

sf::Music* CMusics::GetMusic(MusicID id) {
	if (musics.find(id) == musics.end()) throw;
	return musics.at(id).first;
}

sf::Music* CMusics::CreateMusic(MusicID id, std::string file_path) {
	if (musics.find(id) != musics.end()) throw;

	auto music = new sf::Music();
	auto music_container = std::make_pair(music, file_path);
	musics.insert(std::make_pair(id, music_container));

	return music;
}

sf::Music* CMusics::LoadMusic(MusicID id) {
	if (musics.find(id) == musics.end()) throw;

	auto& music_container = musics.at(id);
	auto music = music_container.first;
	std::string file_path = music_container.second;
	music->openFromFile(file_path);

	return music;
}

void CMusics::DestroyMusic(MusicID id) {
	if (musics.find(id) == musics.end()) throw;

	auto music = musics.at(id).first;
	delete music; music = nullptr;

	musics.erase(id);
}

void CMusics::ClearMusics() {
	for (auto& music_containter : musics) {
		auto music = music_containter.second.first;
		delete music; music = nullptr;
	}
	musics.clear();
}
