#pragma once
#ifndef __REMOTE_OBJECT_H__
#define __REMOTE_OBJECT_H__

#include "common.h"

class CRemoteObject {
private:
	float latest_position_x = 0.0f;
	float latest_position_y = 0.0f;

	float previous_position_x = 0.0f;
	float previous_position_y = 0.0f;

	bool is_local;

public:
	bool IsLocal() { return is_local; }
	void SetLocal(bool value) { is_local = value; }

	void GetInterpolated(float& position_x, float& position_y, float interpolate_value);
	void SetLatestPosition(float position_x, float position_y);
};
typedef CRemoteObject* pRemoteObject;

#endif // !__REMOTE_OBJECT_H__
