#pragma once
#include "Animation.h"
#include "AssetIDs.h"
#include "GameObject.h"
#include "debug.h"


#define BOWSER_BBOX_WIDTH 50
#define BOWSER_BBOX_HEIGHT 50
#define BOWSER_GRAVITY 0.002f
#define BOWSER_WALKING_SPEED 0.05f

#define BOWSER_STATE_WALKING_1 77001
#define BOWSER_STATE_WALKING_2 77002
#define BOWSER_STATE_WALKING_3 77003
#define BOWSER_STATE_WALKING_4 77004

#define BOWSER_STATE_WALKING_BACK_1 78001
#define BOWSER_STATE_WALKING_BACK_2 78002
#define BOWSER_STATE_WALKING_BACK_3 78003
#define BOWSER_STATE_WALKING_BACK_4 78004

#define BOWSER_STATE_BREATH 80001

#define change_time 1000
#define Attack_Time 5000
#define CrashingSpeed 0.6
#define CrashingTime 1900
#define shootTime 1500

class CBowser : public CGameObject
{
protected:
    float ax;
    float ay;
    DWORD chargeTime;
    int state;
    int hp = 15;
    int direction = 1;
    ULONGLONG last_change_time;
    ULONGLONG last_attack;
    bool isAttacking = 0;
    bool isCrashing = 0;
    bool isShooting = 0;
    bool isBreathingFlame = 0;
    
public:
    CBowser(float x, float y) : CGameObject(x, y) {
        vx = BOWSER_WALKING_SPEED;
        ax = 0;
        ay = BOWSER_GRAVITY;
        state = BOWSER_STATE_WALKING_1;
        this->ax = 0;
        SetState(BOWSER_STATE_WALKING_1);
        last_change_time = GetTickCount64();
        last_attack = GetTickCount64();
        isAttacking = 0;
    }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);
    virtual int IsCollidable() { return 1; };
    virtual int IsBlocking() { return 0; }
    virtual void SetState(int state);
    void Crashing();
    void Shooting();
    void BreathFlame();
    void takeDmg();
    int GetHp();
};