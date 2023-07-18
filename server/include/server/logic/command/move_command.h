#pragma once
#ifndef __MOVE_COMMAND_H__
#define __MOVE_COMMAND_H__

#include "engine/framework/command/command.h"

struct CMoveCommand : public CCommand {
	bool is_active = false;
	int8_t movement_x;
	int8_t movement_y;

	CMoveCommand(bool is_client, CommandableID id, NetworkID network_id)
		: CCommand(is_client, id, network_object_id) {
		type = ECommandType::MOVE;
	}
};
typedef CMoveCommand* pMoveCommand;


#endif // !__MOVE_COMMAND_H__
