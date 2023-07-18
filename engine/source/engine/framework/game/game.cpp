#include "engine/framework/game/game.h"

void CGame::LoadGameDataFromJson(json& data) {
	auto& window_settings = data.at("window");
	std::string window_title = window_settings.at("title");
	unsigned int window_width = window_settings.at("width");
	unsigned int window_height = window_settings.at("height");
	float frame_rate = window_settings.at("frame_rate");
	float frame_skip_factor = window_settings.at("frame_skip_factor");

	CreateGameWindow(window_width, window_height, window_title, sf::Style::Titlebar | sf::Style::Close);
	SetFramerate(frame_rate, frame_skip_factor);
}

void CGame::CreateGameWindow(int width, int height, std::string name, sf::Uint32 style) {
	window.create(sf::VideoMode(width, height), name, style);
	window.setFramerateLimit(0);
}

void CGame::SetFramerate(float frame_rate, float frame_skip) {
	ms_per_frame = 1000.f / frame_rate;
	if (frame_skip < 2.0f)
		frame_skip = 2.0f;

	frame_skip_threadhold_factor = frame_skip;
}

void CGame::Run(std::string data_path) {
	Initialize(data_path);
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		PreLoop();

		elapsed_ms += clock.GetMilliseconds();
		clock.Reset();

		if (elapsed_ms >= ms_per_frame) {
			Update(ms_per_frame);
			
			if (elapsed_ms < ms_per_frame * frame_skip_threadhold_factor) {
				window.clear();
				Render();
				window.display();
			}

			elapsed_ms -= ms_per_frame;
		}
		else Sleep(DWORD((ms_per_frame * 0.05f)));

		PostLoop();

	}
	Shutdown();
}