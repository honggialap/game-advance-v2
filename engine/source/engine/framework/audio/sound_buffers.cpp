#include "engine/framework/audio/sound_buffers.h"

CSoundBuffers::CSoundBuffers() {
}

CSoundBuffers::~CSoundBuffers() {
	ClearSoundBuffers();
}

void CSoundBuffers::LoadSoundBuffersFromJson(json& data) {
	if (!data.contains("sound_buffers")) return;

	for (auto& sound_buffer_data : data.at("sound_buffers")) {
		SoundBufferID id = sound_buffer_data.at("id");
		auto sound_buffer = CreateSoundBuffer(id);

		std::string file_path = sound_buffer_data.at("file_path");
		sound_buffer->loadFromFile(file_path);
	}
}

sf::SoundBuffer* CSoundBuffers::GetSoundBuffer(SoundBufferID id) {
	if (sound_buffers.find(id) == sound_buffers.end()) throw;
	return sound_buffers.at(id);
}

sf::SoundBuffer* CSoundBuffers::CreateSoundBuffer(SoundBufferID id) {
	if (sound_buffers.find(id) != sound_buffers.end()) throw;
	
	auto sound_buffer = new sf::SoundBuffer();
	sound_buffers.insert(std::make_pair(id, sound_buffer));
	
	return sound_buffer;
}

void CSoundBuffers::DestroySoundBuffer(SoundBufferID id) {
	if (sound_buffers.find(id) == sound_buffers.end()) throw;

	auto sound_buffer = sound_buffers.at(id);
	delete sound_buffer; sound_buffer = nullptr;

	sound_buffers.erase(id);
}

void CSoundBuffers::ClearSoundBuffers() {
	for (auto& sound_buffer_container : sound_buffers) {
		auto sound_buffer = sound_buffer_container.second;
		delete sound_buffer; sound_buffer = nullptr;
	}
	sound_buffers.clear();
}
