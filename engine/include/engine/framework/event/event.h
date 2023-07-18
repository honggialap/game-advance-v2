#pragma once
#ifndef __EVENT_H__
#define __EVENT_H__

#include "common.h"

class CEventSender;
struct CEvent {
public:
	CEventSender& sender;
	EventType event_type = EEventType::INVALID_EVENT;

public:
	CEvent(CEventSender& sender, EventType event_type);
	virtual ~CEvent() = 0;
};
typedef CEvent* pEvent;

#endif // !__EVENT_H__
