#pragma once
#ifndef __MOVE_COMMAND_H__
#define __MOVE_COMMAND_H__

#include "engine/framework/command/command.h"

struct CMoveCommand : public CCommand {
	int8_t movement_x = 0;
	int8_t movement_y = 0;

	CMoveCommand(
		bool is_client
		, CommandableID id
		, NetworkID network_id
		, int8_t movement_x
		, int8_t movement_y
	)
		: CCommand(is_client, id, network_object_id)
		, movement_x(movement_x)
		, movement_y(movement_y)
	{
		type = ECommandType::MOVE;
	}
};
typedef CMoveCommand* pMoveCommand;


#endif // !__MOVE_COMMAND_H__
