#include "engine/framework/event/event_receiver.h"
#include "engine/framework/event/event_manager.h"

CEventReceiver::CEventReceiver(CEventManager& event_manager) 
	: event_manager(event_manager) {
}

CEventReceiver::~CEventReceiver() {
	event_manager.UnsubcribeReceiver(this);
}

void CEventReceiver::SubcribeEvent(EventType type) {
	event_manager.SubcribeEvent(type, this);
}

void CEventReceiver::UnsubcribeEvent(EventType type) {
	event_manager.UnsubcribeEvent(type, this);
}
