#include "SpikeTurtle.h"
#include <stdlib.h>
#include <time.h>
#include "debug.h"

SpikeTurtle::SpikeTurtle(float x, float y, float left, float right) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SPIKETURTLE_GRAVITY;
	this->left = left;
	this->right = right;
	isSlide = false;
    srand(time(NULL));
    intervalSlide = rand() % 3000 + 1000;
    startSlide = false;
    timer = 0;
	this->vx = SPIKETURTLE_WALKING_SPEED;
	slideTime = 0;
}

void SpikeTurtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - SPIKETURTLE_BBOX_WIDTH / 2;
	top = y - SPIKETURTLE_BBOX_HEIGHT / 2;
	right = left + SPIKETURTLE_BBOX_WIDTH;
	bottom = top + SPIKETURTLE_BBOX_HEIGHT;
}

void SpikeTurtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void SpikeTurtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<SpikeTurtle*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
        if (isSlide) startSlide = true;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void SpikeTurtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    timer += dt * !isSlide;
	if (timer > intervalSlide) {
        isSlide = true;
		timer = 0;
        vy -= 0.01 * (rand() % 50 + 10);
        vx = vx > 0 ? SPIKETURTLE_SLIDE_SPEED : -SPIKETURTLE_SLIDE_SPEED;
        slideTime = rand() % 5000 + 500;
    }
	slideTime -= dt * isSlide * startSlide;
	if (slideTime < 0) {
        isSlide = false;
        slideTime = 0;
        vx = vx > 0 ? SPIKETURTLE_WALKING_SPEED : -SPIKETURTLE_WALKING_SPEED;
    }
	vy += ay * dt;
	vx += ax * dt;

	if (x < left)
	{
		x = left;
		vx = -vx;
	}
	else if (x > right)
	{
		x = right;
		vx = -vx;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void SpikeTurtle::Render()
{
	int aniId;
	if (vx > 0) aniId = ID_ANI_SPIKETURTLE_WALK_RIGHT;
	if (vx <= 0) aniId = ID_ANI_SPIKETURTLE_WALK_LEFT;
	if (isSlide) aniId = ID_ANI_SPIKETURTLE_SLIDE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}