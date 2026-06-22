#pragma once
#include "GameObject.h"
#include "debug.h"

#define SPIKETURTLE_GRAVITY 0.002f
#define SPIKETURTLE_WALKING_SPEED 0.08f
#define SPIKETURTLE_SLIDE_SPEED 0.2f

#define SPIKETURTLE_BBOX_WIDTH 15
#define SPIKETURTLE_BBOX_HEIGHT 14

#define ID_ANI_SPIKETURTLE_WALK_LEFT 72000
#define ID_ANI_SPIKETURTLE_WALK_RIGHT 72100
#define ID_ANI_SPIKETURTLE_SLIDE 72200
#define TIMEOUT_SLIDE 200

class SpikeTurtle : public CGameObject
{
protected:
    float ax;
    float ay;
    float left, right;
    bool isSlide;
    float intervalSlide;
    float timer;
    float slideTime;
    bool startSlide;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);

    virtual void OnCollisionWith(LPCOLLISIONEVENT e);


    void dropSpikeTurtle(float x, float y);
public:
    SpikeTurtle(float x, float y, float left, float right);
};

