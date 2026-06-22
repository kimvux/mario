#pragma once
#include "GameObject.h"

#define SPIKETURTLE_DROPPER_SPEED 0.1f

#define ID_ANI_SPIKETURTLE_DROPPER 72300

class SpikeTurtleDropper : public CGameObject
{
protected:
    float timer;
    float interval;
    float defaultY;
    float ay;
public:
    SpikeTurtleDropper(float x, float y);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual int IsBlocking() { return 0; }
    virtual int IsCollidable() { return 1; };
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

