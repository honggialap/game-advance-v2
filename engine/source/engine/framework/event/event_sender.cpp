#include "engine/framework/event/event_sender.h"
#include "engine/framework/event/event_manager.h"

CEventSender::CEventSender(CEventManager& event_manager)
	: event_manager(event_manager) {
}

CEventSender::~CEventSender() {
}

void CEventSender::QueueEvent(pEvent sending_event) {
	event_manager.QueueEvent(sending_event);
}
