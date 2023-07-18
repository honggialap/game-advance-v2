#pragma once
#ifndef __EVENT_RECEIVER_H__
#define __EVENT_RECEIVER_H__

#include "event.h"

class CEventManager;
class CEventReceiver {
private:
	CEventManager& event_manager;

public:
	CEventReceiver(CEventManager& event_manager);
	virtual ~CEventReceiver() = 0;

	void SubcribeEvent(EventType type);
	void UnsubcribeEvent(EventType type);
	virtual void HandleEvent(pEvent incomming_event) = 0;
};
typedef CEventReceiver* pEventReceiver;

#endif // !__EVENT_RECEIVER_H__
