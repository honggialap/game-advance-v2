#pragma once
#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "common.h"

struct CCommand 
{
public:
	CommandableID commandable_id = INVALID_GAMEOBJECT_ID;
	NetworkID network_object_id = INVALID_GAMEOBJECT_ID;
	CommandType type = ECommandType::INVALID_COMMAND;
	bool is_client;

public:
	CCommand(bool is_client, CommandableID id, NetworkID network_object_id)
		: is_client(is_client)
		, commandable_id(id)
		, network_object_id(network_object_id)
	{}
	virtual ~CCommand() = 0 {}
};
typedef CCommand* pCommand;

#endif // !__COMMAND_H__
