#pragma once
#ifndef __SHOOT_COMMAND_H__
#define __SHOOT_COMMAND_H__

#include "engine/framework/command/command.h"

struct CShootCommand : public CCommand {
	int8_t normal_x;
	int8_t normal_y;

	CShootCommand(
		CommandableID id
		, NetworkID network_object_id
		, int8_t normal_x
		, int8_t normal_y
	)
		: CCommand(true, id, network_object_id)
		, normal_x(normal_x)
		, normal_y(normal_y)
	{
		type = ECommandType::SHOOT;
	}
	~CShootCommand() {}
};
typedef CShootCommand* pShootCommand;

#endif // !__SHOOT_COMMAND_H__
