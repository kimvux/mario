#include "Goomba.h"
#include "Turtle.h"
#include "Mario.h"
#include "PlayScene.h"
#include <stdlib.h>
#include <time.h>
#include "debug.h"

CGoomba::CGoomba(float x, float y, float leftEdge, float rightEdge, int isFlyable) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	this->leftEdge = leftEdge;
	this->rightEdge = rightEdge;
	die_start = -1;
	SetState(GOOMBA_STATE_WALKING);
	isGetHitByTurtleShell = false;
	this->isFlyable = isFlyable;
	timer = 0;
	isFlying = false;
	srand(time(NULL));
	intervalFlying = rand() % 10000 + 1000;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		if (isFlyable) {
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT + 2;
		}
		else {
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
		}
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (e->ny != 0)
	{
		isFlying = false;
		intervalFlying = rand() % 10000 + 1000;
		vy = 0;
		vx = vx > 0 ? GOOMBA_WALKING_SPEED : -GOOMBA_WALKING_SPEED;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<Turtle*>(e->obj) && dynamic_cast<Turtle*>(e->obj)->IsSlide()) {
		getHitByTurtleShell();
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	timer += dt * !isFlying;
	if (isFlyable && timer >= intervalFlying)
	{
		isFlying = true;
		timer = 0;
		vy = -0.01 * (rand() % 50 + 10);
		vx = vx > 0 ? GOOMBA_WALKING_SPEED * 3 : -GOOMBA_WALKING_SPEED * 3;
	}
	if (isGetHitByTurtleShell) {
		vy += ay * dt;
		y += vy * dt;
		return;
	}
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if (x <= leftEdge || x >= rightEdge) vx = -vx;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId;
	if (isFlyable) {
		if (vy == 0) {
			aniId = ID_ANI_GOOMBA_WALKING_FLYABLE;
		}
		else {
			aniId = ID_ANI_GOOMBA_FLYING_FLYABLE;
		}
	}
	else {
		aniId = ID_ANI_GOOMBA_WALKING;
	}
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}

void CGoomba::getHitByTurtleShell() {
	isGetHitByTurtleShell = true;
	vx = 0;
	vy = -0.3f;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	mario->addCoin(2);
}
