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

void CTank::Shoot(float x, float y, bool left, bool up) {
	for (auto& bullet : bullets) {
		if (!bullet->IsShot()) {
			bullet->Shoot(x, y, left, up);
			return;
		}
	}
}
