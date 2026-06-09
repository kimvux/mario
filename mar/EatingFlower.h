#pragma once
#include "GameObject.h"



#define FLOWER_BBOX_WIDTH 10
#define FLOWER_BBOX_HEIGHT 10

#define FLOWER_STATE_OPEN_MOUTH 68000
#define FLOWER_STATE_CLOSED_MOUTH 68500
#define ID_ANI_FLOWER_OPEN 68000   // ID Animation khi mở mồm
#define ID_ANI_FLOWER_CLOSED 68500

#define coolDown 600


class CFlower : public CGameObject
{
protected:
	ULONGLONG lastBiteTime;
	bool IsOpen;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 0; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	CFlower(float x, float y);
	virtual void SetState(int state);
};