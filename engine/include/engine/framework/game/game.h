#pragma once
#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"

class CGame {
protected:
	sf::RenderWindow window;
	b2Timer clock;
	float elapsed_ms = 0.0f;
	float ms_per_frame = 0.0f;
	float frame_skip_threadhold_factor = 0.0f;

public:
	virtual void Initialize(std::string data_path) = 0;
	virtual void Shutdown() = 0;

	void LoadGameDataFromJson(json& data);

	void CreateGameWindow(int width, int height, std::string name, sf::Uint32 style = 7U);
	sf::RenderWindow& GetGameWindow() { return window; }

	void SetFramerate(float frame_rate, float frame_skip_factor);

	void Run(std::string data_path);
	void Exit() { window.close(); }

	virtual void PreLoop() = 0;
	virtual void Update(float elapsed_ms) = 0;
	virtual void Render() = 0;;
	virtual void PostLoop() = 0;
};
typedef CGame* pGame;

#endif // !__GAME_H__
