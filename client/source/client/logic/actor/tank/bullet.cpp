#include "client/logic/actor/tank/bullet.h"
#include "client/logic/actor/tank/tank.h"

void CBullet::SetTank(pTank tank) {
	this->tank = tank;
	tank->AddBullet(this);
}

void CBullet::Shoot(float x, float y, bool left, bool up) {
	is_shot = true;
	OnShoot(x, y, left, up);
}

void CBullet::Impact() {
	is_shot = false;
	OnImpact();
}
