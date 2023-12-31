#pragma once
#ifndef __SHOOT_COMMAND_H__
#define __SHOOT_COMMAND_H__

#include "engine/framework/command/command.h"

struct CShootCommand : public CCommand {
	int8_t normal_x = 0;
	int8_t normal_y = 0;

	CShootCommand(
		bool is_client
		, CommandableID id
		, NetworkID network_id
		, int8_t movement_x
		, int8_t movement_y
	)
		: CCommand(is_client, id, network_object_id)
		, normal_x(normal_x)
		, normal_y(normal_y)
	{
		type = ECommandType::SHOOT;
	}
};
typedef CShootCommand* pShootCommand;

#endif //!__SHOOT_COMMAND_H__
