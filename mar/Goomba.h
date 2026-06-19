#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.001f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_WALKING_FLYABLE 5002
#define ID_ANI_GOOMBA_FLYING_FLYABLE 5003
#define ID_ANI_GOOMBA_DIE 5001

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	float leftEdge;
	float rightEdge;
	ULONGLONG die_start;
	bool isGetHitByTurtleShell;
	int isFlyable;
	float timer;
	bool isFlying;
	float intervalFlying;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoomba(float x, float y, float leftEdge, float rightEdge, int isflyable);
	virtual void SetState(int state);
	void getHitByTurtleShell();
	void disableFly() { isFlyable = false; ay = GOOMBA_GRAVITY; isFlying = false; timer = 0; vy = -0.1f; }
	bool IsFlyable() { return isFlyable; }
};