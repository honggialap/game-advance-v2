#include "client/logic/actor/tank/tank.h"

void CTank::AddBullet(pBullet bullet) {
	bullets.push_back(bullet);
}

bool CTank::IsShootable() {
	for (auto& bullet : bullets) {
		if (!bullet->IsShot())
			return true;
	}

	return false;
}

void CTank::Shoot(float x, float y, int8_t normal_x, int8_t normal_y) {
	for (auto& bullet : bullets) {
		if (!bullet->IsShot()) {
			bullet->Shoot(x, y, normal_x, normal_y);
			return;
		}
	}
}
