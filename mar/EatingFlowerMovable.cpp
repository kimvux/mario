#include "EatingFlowerMovable.h"
#include "debug.h"

EatingFlowerMovable::EatingFlowerMovable(float x, float y, int flowerType) : CGameObject(x, y) {
    this->flowerType = flowerType;
    if (flowerType != 0) {
        this->ay = EATINGFLOWER_GRAVITY;
        this->ax = 0;
        vx = EATINGFLOWER_MOVESPEED;
    }
    else {
        this->ax = 0;
        this->ay = 0;
        this->vx = 0;
        this->vy = EATINGFLOWER_GROWSPEED;
    }
    defaultY = y;
    timer = 0;
    isGrowing = false;
}

void EatingFlowerMovable::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    if (flowerType != 0) {
        vy += ay * dt;
        vx += ax * dt;
    }
    else {
        timer += dt * !isGrowing;
        if (timer > GROWING_INTERVAL) {
            isGrowing = true;
            timer = 0;
        }
        y += vy * dt * isGrowing;
        if (y > defaultY || y < defaultY - 25) {
            isGrowing = false;
            vy = -vy;
            y = y > defaultY ? defaultY : defaultY - 25;
        }
    }
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void EatingFlowerMovable::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
    if (isGrowing && flowerType == 0) {
        left = x - FLOWER_BBOX_WIDTH / 2;
        top = y - FLOWER_BBOX_HEIGHT / 2 + 10;
        right = left + FLOWER_BBOX_WIDTH;
        bottom = top + FLOWER_BBOX_HEIGHT;
    }
    else {
        left = x - FLOWER_BBOX_WIDTH / 2;
        top = y - FLOWER_BBOX_HEIGHT / 2 + 5;
        right = left + FLOWER_BBOX_WIDTH;
        bottom = top + FLOWER_BBOX_HEIGHT - 5;
    }
}

void EatingFlowerMovable::Render() {
    int ani_id;
    if (flowerType == 0) ani_id = ID_ANI_EATINGFLOWER_UPDOWN;
    else ani_id = ID_ANI_EATINGFLOWER_MOVEJUMP;
    CAnimations::GetInstance()->Get(ani_id)->Render(x, y);
}

void EatingFlowerMovable::OnNoCollision(DWORD dt) {
    if (flowerType != 0) {
        x += vx * dt;
        y += vy * dt;
    }
}

void EatingFlowerMovable::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (!e->obj->IsBlocking()) return;
    if (e->ny != 0) {
        vy = 0;
    }
    if (e->nx != 0) {
        vx = -vx;
    }
}