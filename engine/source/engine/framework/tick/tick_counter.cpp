#include "engine/framework/tick/tick_counter.h"

Tick CTickCounter::GetLatestTick() {
	return latest_tick;
}

void CTickCounter::SetLatestTick(Tick value) {
	latest_tick = value;
}

void CTickCounter::IncreaseLatestTick() {
	latest_tick += 1;
}

Tick CTickCounter::GetTickPerGameState() {
	return tick_per_game_state;
}

void CTickCounter::SetTickPerGameState(Tick value) {
	tick_per_game_state = value;
}
