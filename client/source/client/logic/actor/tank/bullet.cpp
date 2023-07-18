#include "client/logic/actor/tank/bullet.h"
#include "client/logic/actor/tank/tank.h"

void CBullet::SetTank(pTank tank) {
	this->tank = tank;
	tank->AddBullet(this);
}

void CBullet::Shoot(float x, float y, int8_t normal_x, int8_t normal_y) {
	is_shot = true;
	OnShoot(x, y, normal_x, normal_y);
}

void CBullet::Impact() {
	is_shot = false;
	OnImpact();
}
