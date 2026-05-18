#pragma once
#include "GameObject.h"



#define TURRET_BBOX_WIDTH 10
#define TURRET_BBOX_HEIGHT 10

#define TURRET_STATE_NORMAL 67000

#define coolDown 3000


class CTurret : public CGameObject
{
protected:
	int dir;
	int lastShotTime;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CTurret(float x, float y, int dir);
	virtual void SetState(int state);
	void SpawnBullet();
};