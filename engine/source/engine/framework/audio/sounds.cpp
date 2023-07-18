#include "engine/framework/audio/sounds.h"

CSounds::CSounds(CSoundBuffers& sound_buffers)
	: sound_buffers(sound_buffers) {
}

CSounds::~CSounds() {
	ClearSounds();
}

void CSounds::LoadSoundsFromJson(json& data) {
	if (!data.contains("sounds")) return;

	for (auto& sound_data : data.at("sounds")) {
		SoundID id = sound_data.at("id");
		auto sound = CreateSound(id);

		SoundBufferID sound_buffer_id = sound_data.at("sound_buffer_id");
		auto sound_buffer = sound_buffers.GetSoundBuffer(sound_buffer_id);

		sound->setBuffer(*sound_buffer);
	}
}

sf::Sound* CSounds::GetSound(SoundID id) {
	if (sounds.find(id) == sounds.end()) throw;
	return sounds.at(id);
}

sf::Sound* CSounds::CreateSound(SoundID id) {
	if (sounds.find(id) != sounds.end()) throw;

	auto sound = new sf::Sound();
	sounds.insert(std::make_pair(id, sound));

	return sound;
}

void CSounds::DestroySound(SoundID id) {
	if (sounds.find(id) == sounds.end()) throw;

	auto sound = sounds.at(id);
	delete sound; sound = nullptr;

	sounds.erase(id);
}

void CSounds::ClearSounds() {
	for (auto& sound_container : sounds) {
		auto sound = sound_container.second;
		delete sound; sound = nullptr;
	}
	sounds.clear();
}
