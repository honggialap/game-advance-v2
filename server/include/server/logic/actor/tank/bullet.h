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
	pTank GetTank() { return tank; }

	void SetShot(bool value) { is_shot = value; }
	bool IsShot() { return is_shot; }

	void Shoot(float x, float y, int8_t nx, int8_t ny);
	void Impact();

	virtual void OnShoot(float x, float y, int8_t nx, int8_t ny) = 0;
	virtual void OnImpact() = 0;
};
typedef CBullet* pBullet;

#endif // !__BULLET_H__
