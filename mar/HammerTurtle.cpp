#include "HammerTurtle.h"
#include "Hammer.h"
#include "PlayScene.h"

void HammerTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
    left = x - HAMMER_TURTLE_BBOX_WIDTH / 2;
    top = y - HAMMER_TURTLE_BBOX_HEIGHT / 2;
    right = left + HAMMER_TURTLE_BBOX_WIDTH;
    bottom = top + HAMMER_TURTLE_BBOX_HEIGHT;
}

void HammerTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    vy += ay * dt;
    vx += ax * dt;
    if (x < left)
    {
        x = left;
        vx = -vx;
        direction = 1;
    }
    else if (x > right)
    {
        x = right;
        vx = -vx;
        direction = -1;
    }
    if (!isThrowing && GetTickCount() - lastThrowTime > throwInterval)
    {
        isThrowing = true;
        chargeTime = GetTickCount();
        SetState(HAMMER_TURTLE_STATE_THROW);
    }
    if (isThrowing && GetTickCount() - chargeTime > CHARGE_TIME){
        ThrowHammer();
        chargeTime = 0;
        isThrowing = false;
        lastThrowTime = GetTickCount();
        SetState(HAMMER_TURTLE_STATE_WALK);
    }
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void HammerTurtle::Render() {
    int aniId;
    if (vx > 0 && !isThrowing) aniId = ID_ANI_HAMMERTURTLE_WALK_RIGTH;
    else if (vx < 0 && !isThrowing) aniId = ID_ANI_HAMMERTURTLE_WALK_LEFT;
    else if (isThrowing && direction == 1) aniId = ID_ANI_HAMMERTURTLE_THROW_RIGHT;
    else if (isThrowing && direction == -1) aniId = ID_ANI_HAMMERTURTLE_THROW_LEFT;
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(aniId)->Render(x, y);
}

void HammerTurtle::OnNoCollision(DWORD dt) {
    x += vx * dt;
    y += vy * dt;
}

void HammerTurtle::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<HammerTurtle*>(e->obj)) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
        vx = -vx;
        direction = -direction;
    }
}

void HammerTurtle::SetState(int state) {
    CGameObject::SetState(state);
    switch (state) {
    case HAMMER_TURTLE_STATE_WALK:
        vx = HAMMER_TURTLE_WALKING_SPEED * direction;
        break;
    case HAMMER_TURTLE_STATE_THROW:
        vx = 0;
        break;
    }
}

void HammerTurtle::ThrowHammer() {
    Hammer* hammer = new Hammer(x + 20 * direction, y - 20, throwStrength, direction);
    ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(hammer);
}