#pragma once
#ifndef __SHOOT_COMMAND_H__
#define __SHOOT_COMMAND_H__

#include "engine/framework/command/command.h"

struct CShootCommand : public CCommand {
	bool is_active = false;
	int8_t movement_x;
	int8_t movement_y;

	CShootCommand(bool is_client, CommandableID id, NetworkID network_id)
		: CCommand(is_client, id, network_object_id) {
		type = ECommandType::SHOOT;
	}
};
typedef CShootCommand* pShootCommand;

#endif //!__SHOOT_COMMAND_H__
