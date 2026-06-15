#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_STAR 60000

#define	STAR_WIDTH 10
#define STAR_BBOX_WIDTH 10
#define STAR_BBOX_HEIGHT 16

class CSTAR : public CGameObject {
protected:
	float ax;
	float ay;
	float defaultY;
	bool isGrowUp;
public:
	CSTAR(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = 0.002f;
		this->vx = 0;
		isGrowUp = true;
		defaultY = y - 16;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	void GrowUp(DWORD dt);
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
