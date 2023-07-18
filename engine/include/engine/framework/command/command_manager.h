#pragma once
#ifndef __COMMAND_MANAGER_H__
#define __COMMAND_MANAGER_H__

#include "commandable.h"

class CCommandManager {
private:
	std::map<Tick, std::vector<pCommand>> commands;
	std::map<CommandableID, pCommandable> commandables;

public:
	std::vector<pCommand>& GetCommandsAtTick(Tick tick);
	void AddCommandAtTick(Tick tick, pCommand command);
	
	void TrimServerCommandsOnly(Tick from, Tick to);
	void TrimServerCommandsOnly(Tick before);

	void TrimCommands(Tick from, Tick to);
	void TrimCommands(Tick before);
	void ClearCommands();

	void AddCommandable(pCommandable commandable);
	void RemoveCommandable(pCommandable commandable);

	void ExecuteCommands(Tick tick);
};

#endif // !__COMMAND_MANAGER_H__