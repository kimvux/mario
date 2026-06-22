#pragma once
#include "GameObject.h"

#define BULLET_GRAVITY 0.00f
#define BULLET_FLYING_SPEED 0.15f


#define BULLET_BBOX_WIDTH 10
#define BULLET_BBOX_HEIGHT 10

#define ID_ANI_BULLET_HORIZONTAL 6000
#define ID_ANI_BULLET_VERTICAL   6001


#define BULLET_STATE_FLYING 67


class CBullet : public CGameObject
{
protected:
	float ax;
	float ay;
	int direction;
	bool isCollided;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CBullet(float x, float y, int direction);
	virtual void SetState(int state);
};