#pragma once
#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "event_sender.h"
#include "event_receiver.h"

class CEventManager {
private:
	std::multimap<EventType, pEventReceiver> event_listeners;
	std::queue<pEvent> events;

public:
	void SubcribeEvent(EventType event_type, pEventReceiver receiver);
	void UnsubcribeEvent(EventType event_type, pEventReceiver receiver);
	void UnsubcribeReceiver(pEventReceiver receiver);

	void QueueEvent(pEvent event);
	void HandleEvent();
};
typedef CEventManager* pEventManager;

#endif // !__EVENT_MANAGER_H__
