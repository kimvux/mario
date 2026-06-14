#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_MUSHROOM 62000

#define	MUSHROOM_WIDTH 15
#define MUSHROOM_BBOX_WIDTH 15
#define MUSHROOM_BBOX_HEIGHT 15

class Mushroom : public CGameObject {
protected:
	float ax;
	float ay;
public:
	Mushroom(float x, float y) : CGameObject(x, y) {
		this->ax = 0;
		this->ay = 0.002f;
		this->vx = 0.05f;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};
