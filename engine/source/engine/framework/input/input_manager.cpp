#include "engine/framework/input/input_manager.h"

void CInputManager::AddInputHandler(pInputHandler input_handler) {
	input_handlers.push_back(input_handler);
}

void CInputManager::RemoveInputHandler(pInputHandler input_handler) {
	input_handlers.erase(
		std::remove(input_handlers.begin(), input_handlers.end(), input_handler)
		, input_handlers.end()
	);
}

void CInputManager::HandleInput(Tick tick) {
	for (auto& input_handler : input_handlers) {
		input_handler->HandleInput(tick);
	}
}
