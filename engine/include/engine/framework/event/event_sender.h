#pragma once
#ifndef __EVENT_SENDER_H__
#define __EVENT_SENDER_H__

#include "event.h"

class CEventManager;
class CEventSender {
private:
	CEventManager& event_manager;

public:
	CEventSender(CEventManager& event_manager);
	virtual ~CEventSender();

	void QueueEvent(pEvent sending_event);
};
typedef CEventSender* pEventSender;

#endif // !__EVENT_SENDER_H__
