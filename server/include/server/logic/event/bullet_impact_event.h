#pragma once
#ifndef __BULLET_IMPACT_EVENT_H__
#define __BULLET_IMPACT_EVENT_H__

#include "engine/framework/event/event.h"
#include "engine/framework/physics/body.h"

struct CBulletImpactEvent : public CEvent {
	int8_t normal_x = 0;
	int8_t normal_y = 0;
	pBody other = nullptr;

	CBulletImpactEvent(
		CEventSender* sender
		, int8_t normal_x
		, int8_t normal_y
		, pBody other
	)
		: CEvent(sender, EEventType::BULLET_IMPACT_EVENT)
		, normal_x(normal_x)
		, normal_y(normal_y)
		, other(other)
	{}
	~CBulletImpactEvent() {}
};
typedef CBulletImpactEvent* pBulletImpactEvent;

#endif // !__BULLET_IMPACT_EVENT_H__
