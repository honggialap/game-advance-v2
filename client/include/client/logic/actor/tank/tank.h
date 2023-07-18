#pragma once
#ifndef __TANK_H__
#define __TANK_H__

#include "common.h"
#include "bullet.h"

class CTank {
protected:
	std::vector<pBullet> bullets;

public:
	void AddBullet(pBullet bullet);

	bool IsShootable();
	void Shoot(float x, float y, int8_t normal_x, int8_t normal_y);
};
typedef CTank* pTank;

#endif // !__TANK_H__