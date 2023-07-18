#include "engine/framework/event/event.h"
#include "engine/framework/event/event_sender.h"

CEvent::CEvent(CEventSender& sender, EventType event_type)
	: sender(sender) 
	, event_type(event_type) {
}

CEvent::~CEvent() {
}
