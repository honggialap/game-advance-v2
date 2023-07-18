#pragma once
#ifndef __TICK_COUNTER_H__
#define __TICK_COUNTER_H__

#include "common.h"

class CTickCounter {
private:
	Tick latest_tick = 0;
	Tick tick_per_game_state = 0;

public:
	Tick GetLatestTick();
	void SetLatestTick(Tick value);
	void IncreaseLatestTick();

	Tick GetTickPerGameState();
	void SetTickPerGameState(Tick value);
};
typedef CTickCounter* pTickCounter;

#endif // !__TICK_COUNTER_H__
