#include "client/framework/game_object/remote_object.h"

void CRemoteObject::GetInterpolated(float& position_x, float& position_y, float interpolate_value) {
	float delta_x = latest_position_x - previous_position_x;
	position_x = previous_position_x + (delta_x * interpolate_value);

	float delta_y = latest_position_y - previous_position_y;
	position_y = previous_position_y + (delta_y * interpolate_value);
}

void CRemoteObject::SetLatestPosition(float position_x, float position_y) {
	previous_position_x = latest_position_x;
	latest_position_x = position_x;

	previous_position_y = latest_position_y;
	latest_position_y = position_y;
}
