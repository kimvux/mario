#pragma once
#include "GameObject.h"

#define FLOWER_BBOX_WIDTH 15
#define FLOWER_BBOX_HEIGHT 22

#define ID_ANI_EATINGFLOWER_UPDOWN 68100
#define ID_ANI_EATINGFLOWER_MOVEJUMP 68200

#define EATINGFLOWER_MOVESPEED 0.05f
#define EATINGFLOWER_GRAVITY 0.002f
#define EATINGFLOWER_GROWSPEED 0.03f

#define GROWING_INTERVAL 2000

class EatingFlowerMovable : public CGameObject
{
protected:
	int flowerType;
	float ax;
	float ay;
	float defaultY;
	float timer;
	bool isGrowing;
public:
	EatingFlowerMovable(float x, float y, int flowerType);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() {
		if (flowerType == 0) return 0;
		return 1;
	};
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};