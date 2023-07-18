#include "engine/framework/command/commandable.h"
#include "engine/framework/command/command_manager.h"

CCommandable::CCommandable(CCommandManager& command_manager, CommandableID id)
	: command_manager(command_manager) 
	, commandable_id(id) {
	command_manager.AddCommandable(this);
}

CCommandable::~CCommandable() {
	command_manager.RemoveCommandable(this);
}

void CCommandable::Command(Tick tick, pCommand command) {
	command_manager.AddCommandAtTick(tick, command);
}