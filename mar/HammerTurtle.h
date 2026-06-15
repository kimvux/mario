#pragma once
#include "GameObject.h"
#include "debug.h"
#include "Animation.h"
#include "AssetIDs.h"

#define HAMMER_TURTLE_GRAVITY 0.002f
#define HAMMER_TURTLE_WALKING_SPEED 0.05f
#define HAMMER_TURTLE_STATE_WALK 1
#define HAMMER_TURTLE_STATE_THROW 2

#define HAMMER_TURTLE_BBOX_WIDTH 30
#define HAMMER_TURTLE_BBOX_HEIGHT 30

#define CHARGE_TIME 500

class HammerTurtle : public CGameObject
{
protected:
    float ax;
    float ay;
    float left;
    float right;
    bool isThrowing;
    DWORD chargeTime;
    int direction;
    float throwInterval;
    DWORD lastThrowTime;
    float throwStrength;
public:
    HammerTurtle(float x, float y, float left, float right, float throwInterval, float throwStrength) : CGameObject(x, y) {
        vx = HAMMER_TURTLE_WALKING_SPEED;
        ax = 0;
        ay = HAMMER_TURTLE_GRAVITY;
        this->left = left;
        this->right = right;
        isThrowing = false;
        chargeTime = 0;
        direction = 1;
        this->throwInterval = throwInterval;
        this->throwStrength = throwStrength;
        lastThrowTime = GetTickCount();
    };
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void SetState(int state);
    void ThrowHammer();
};

