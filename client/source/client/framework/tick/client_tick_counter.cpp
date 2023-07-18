#include "client/framework/tick/client_tick_counter.h"

Tick CClientTickCounter::GetReconcileTick() {
	return reconcile_tick;
}

void CClientTickCounter::SetReconcileTick(Tick value) {
	reconcile_tick = value;
}

bool CClientTickCounter::IsReconcile() {
	return reconcile_flag;
}

void CClientTickCounter::SetReconcile(bool value) {
	reconcile_flag = value;
}

Tick CClientTickCounter::GetSyncTick() {
	return sync_tick;
}

void CClientTickCounter::IncreaseSyncTick() {
	sync_tick += 1;
}
