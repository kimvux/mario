#pragma once
#include "GameObject.h"
#include "debug.h"

#define TURTLE_GRAVITY 0.002f
#define TURTLE_WALKING_SPEED 0.08f
#define TURTLE_SLIDE_SPEED 0.35f

#define TURTLE_BBOX_WIDTH 22
#define TURTLE_BBOX_HEIGHT 30
#define TURTLE_BBOX_HEIGHT_DIE 20

#define ID_ANI_TURTLE_WALKING 71000
#define ID_ANI_TURTLE_DIE 71100
#define ID_ANI_TURTLE_WALKING_FLIP 71200
#define TIMEOUT_SLIDE 200

class Turtle : public CGameObject
{
protected:
	float ax;
	float ay;
	float left, right;
	bool isDie;
	bool isSlide;
	float timeSlide;
	bool timeSlideStartSet;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	Turtle(float x, float y, float left, float right);
	void Kill();
	bool IsDie() { return isDie; }
	void slide(float direction);
	bool IsSlide() { return isSlide; }
};