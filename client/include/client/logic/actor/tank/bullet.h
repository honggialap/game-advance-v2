#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "common.h"

class CTank;
typedef CTank* pTank;

class CBullet {
protected:
	pTank tank = nullptr;
	bool is_shot = false;

public:
	void SetTank(pTank tank);

	bool IsShot();

	void Shoot(float x, float y, bool left, bool up);
	void Impact();

	virtual void OnShoot(float x, float y, bool left, bool up) = 0;
	virtual void OnImpact() = 0;
};
typedef CBullet* pBullet;

#endif // !__BULLET_H__
