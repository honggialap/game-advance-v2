#include "engine/framework/input/input_handler.h"
#include "engine/framework/input/input_manager.h"

CInputHandler::CInputHandler(CInputManager& input_manager)
	: input_manager(input_manager) {
	input_manager.AddInputHandler(this);
}

CInputHandler::~CInputHandler() {
	input_manager.RemoveInputHandler(this);
}
