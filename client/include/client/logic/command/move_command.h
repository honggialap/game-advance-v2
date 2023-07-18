#pragma once
#ifndef __MOVE_COMMAND_H__
#define __MOVE_COMMAND_H__

#include "engine/framework/command/command.h"

struct CMoveCommand : public CCommand {
	int8_t movement_x;
	int8_t movement_y;

	CMoveCommand(
		CommandableID id
		, NetworkID network_object_id
		, int8_t movement_x
		, int8_t movement_y
	)
		: CCommand(true, id, network_object_id)
		, movement_x(movement_x)
		, movement_y(movement_y)
	{
		type = ECommandType::MOVE;
	}
	~CMoveCommand() {}

};
typedef CMoveCommand* pMoveCommand;

#endif // !__MOVE_COMMAND_H__
