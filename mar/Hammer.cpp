#include "Hammer.h"
#include "Game.h"
#include "Mario.h"

void Hammer::GetBoundingBox(float &left, float &top, float &right, float &bottom) {
    left = x - HAMMER_BBOX_WIDTH/2;
    top = y - HAMMER_BBOX_HEIGHT/2;
    right = left + HAMMER_BBOX_WIDTH;
    bottom = top + HAMMER_BBOX_HEIGHT;
}

void Hammer::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {
    vx += ax * dt;
    vy += ay * dt;
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
    if (y >= 600) this->Delete();
}

void Hammer::Render() {
    int aniId;
    if (direction == 1) aniId = ID_ANI_HAMMER_RIGHT;
    else aniId = ID_ANI_HAMMER_LEFT;
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(aniId)->Render(x, y);
}

void Hammer::OnNoCollision(DWORD dt) {
    x += vx * direction * dt;
    y += vy * dt;
}

void Hammer::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (dynamic_cast<CMario*>(e->obj)) {
        CMario* mario = dynamic_cast<CMario*>(e->obj);
        mario->getHitByHammer();
    }
}