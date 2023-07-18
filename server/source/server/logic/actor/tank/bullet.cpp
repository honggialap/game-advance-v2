#include "server/logic/actor/tank/bullet.h"
#include "server/logic/actor/tank/tank.h"

void CBullet::SetTank(pTank tank) {
	this->tank = tank;
	tank->AddBullet(this);
}

bool CBullet::IsShot() {
	return is_shot;
}

void CBullet::Shoot(float x, float y, int8_t nx, int8_t ny) {
	is_shot = true;
	OnShoot(x, y, nx, ny);
}

void CBullet::Impact() {
	is_shot = false;
	OnImpact();
}
