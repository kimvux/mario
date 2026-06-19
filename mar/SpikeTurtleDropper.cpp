#include "SpikeTurtleDropper.h"
#include "SpikeTurtle.h"
#include "debug.h"
#include <stdlib.h>
#include <time.h>
#include "PlayScene.h"

SpikeTurtleDropper::SpikeTurtleDropper(float x, float y) : CGameObject(x, y) {
    vx = SPIKETURTLE_DROPPER_SPEED;
    ay = 0.0001f;
    timer = 0;
    srand(time(NULL));
    interval = rand() % 8000 + 1000;
    defaultY = y;
}

void SpikeTurtleDropper::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
    left = x - 5;
    top = y - 5;
    right = x + 5;
    bottom = y + 5;
}

void SpikeTurtleDropper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    timer += dt;
    if (timer > interval) {
        timer = 0;
        interval = rand() % 8000 + 1000;
        SpikeTurtle* p = new SpikeTurtle(x, y, x - 1000, x + 1000);
        ((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddObject(p);
    }
    if (y > defaultY + 20) {
        vy -= 0.035f;
    }
    if (y < 0) {
        vy = 0;
    }
    vy += ay * dt;
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void SpikeTurtleDropper::Render() {
    CAnimations::GetInstance()->Get(ID_ANI_SPIKETURTLE_DROPPER)->Render(x, y);
}

void SpikeTurtleDropper::OnNoCollision(DWORD dt) {
    y += vy * dt;
    x += vx * dt;
}

void SpikeTurtleDropper::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (e->nx != 0 && e->obj->IsBlocking()) {
        vx = -vx;
    }
}