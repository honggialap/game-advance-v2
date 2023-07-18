#pragma once
#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "input_handler.h"

class CInputManager {
private:
	std::vector<pInputHandler> input_handlers;

public:
	void AddInputHandler(pInputHandler input_handler);
	void RemoveInputHandler(pInputHandler input_handler);

	void HandleInput(Tick tick);
};
typedef CInputManager* pInputManager;

#endif // !__INPUT_MANAGER_H__
