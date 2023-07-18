#include "engine/framework/event/event_manager.h"

void CEventManager::SubcribeEvent(EventType event_type, pEventReceiver receiver) {
	event_listeners.emplace(event_type, receiver);
}

void CEventManager::UnsubcribeEvent(EventType event_type, pEventReceiver receiver) {
	auto range = event_listeners.equal_range(event_type);
	for (auto& iterator = range.first; iterator != range.second;) {
		if ((*iterator).second != receiver) {
			iterator++;
			continue;
		}

		event_listeners.erase(iterator);
	}
}

void CEventManager::UnsubcribeReceiver(pEventReceiver receiver) {
	for (auto iterator = event_listeners.begin(); iterator != event_listeners.end();) {
		if ((*iterator).second != receiver) {
			iterator++;
			continue;
		}

		event_listeners.erase(iterator);
	}
}

void CEventManager::QueueEvent(pEvent incomming_event) {
	events.push(incomming_event);
}

void CEventManager::HandleEvent() {
	while (!events.empty()) {
		pEvent sending_event = events.front();
		EventType event_type = sending_event->event_type;
		auto range = event_listeners.equal_range(event_type);
		for (auto& iterator = range.first; iterator != range.second;) {
			(*iterator).second->HandleEvent(sending_event);
		}
		delete sending_event;
		sending_event = nullptr;
		events.pop();
	}
}