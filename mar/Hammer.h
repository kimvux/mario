#pragma once
#include "GameObject.h"
#include "AssetIDs.h"
#define HAMMER_BBOX_WIDTH 13
#define HAMMER_BBOX_HEIGHT 13
#define HAMMER_GRAVITY 0.0002f

class Hammer : public CGameObject
{
protected:
	float ax;
    float ay;
    int direction;
public:
	Hammer(float x, float y, float strength, int direction) : CGameObject(x, y){
        this->ax = 0;
        this->ay = HAMMER_GRAVITY;
        this->direction = direction;
        this->vx = strength;
        this->vy = -strength * 0.7f;
    };
    virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 0; };
    virtual void OnCollisionWith(LPCOLLISIONEVENT e){};
    virtual void OnNoCollision(DWORD dt);
};

