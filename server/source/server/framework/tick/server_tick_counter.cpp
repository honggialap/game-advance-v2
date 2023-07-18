#include "server/framework/tick/server_tick_counter.h"

Tick CServerTickCounter::GetRollbackTick() {
	return rollback_tick;
}

void CServerTickCounter::SetRollbackTick(Tick value) {
	rollback_tick = value;
}

bool CServerTickCounter::IsRollback() {
	return rollback_flag;
}

void CServerTickCounter::SetRollback(bool value) {
	rollback_flag = value;
}
