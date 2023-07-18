#pragma once
#ifndef __SERVER_TICK_COUNTER_H__
#define __SERVER_TICK_COUNTER_H__

#include "engine/framework/framework.h"

class CServerTickCounter
	: public CTickCounter
{
private:
	Tick rollback_tick = 0;
	bool rollback_flag = false;

public:
	Tick GetRollbackTick();
	void SetRollbackTick(Tick value);

	bool IsRollback();
	void SetRollback(bool value);
};
typedef CServerTickCounter* pServerTickCounter;

#endif // !__SERVER_TICK_COUNTER_H__
