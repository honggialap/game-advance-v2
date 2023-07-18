#pragma once
#ifndef __COMMANDABLE_H__
#define __COMMANDABLE_H__

#include "command.h"

class CCommandManager;
class CCommandable {
private:
	CCommandManager& command_manager;
	CommandableID commandable_id = INVALID_GAMEOBJECT_ID;

public:
	CCommandable(CCommandManager& command_manager, CommandableID id);
	virtual ~CCommandable() = 0;
	
	CCommandManager& GetCommandManager() { return command_manager; }
	CommandableID GetCommandableID() { return commandable_id; }

	void Command(Tick tick, pCommand command);
	virtual void ExecuteCommand(pCommand command) = 0;
};
typedef CCommandable* pCommandable;

#endif // !__COMMANDABLE_H__
