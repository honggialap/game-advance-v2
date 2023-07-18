#pragma once
#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANLDER_H__

#include "common.h"

class CInputManager;
class CInputHandler {
private:
	CInputManager& input_manager;

public:
	CInputHandler(CInputManager& input_manager);
	~CInputHandler();

	virtual void HandleInput(Tick tick) = 0;
};
typedef CInputHandler* pInputHandler;


#endif // !__INPUT_HANDLER_H__
