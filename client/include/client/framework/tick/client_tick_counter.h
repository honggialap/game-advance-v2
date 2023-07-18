#pragma once
#ifndef __CLIENT_TICK_COUNTER_H__
#define __CLIENT_TICK_COUNTER_H__

#include "engine/framework/framework.h"

class CClientTickCounter 
	: public CTickCounter
{
private:
	Tick reconcile_tick = 0;
	bool reconcile_flag = false;

	Tick sync_tick = 0;

public:
	Tick GetReconcileTick();
	void SetReconcileTick(Tick value);

	bool IsReconcile();
	void SetReconcile(bool value);

	Tick GetSyncTick();
	void IncreaseSyncTick();
};
typedef CClientTickCounter* pClientTickCounter;

#endif // !__CLIENT_TICK_COUNTER_H__
