#include "RFlame.h"
#include "PlayScene.h"

RFlame::RFlame(float x, float y, bool direction) {
	this -> ax = 0;
	this -> ay = RFLAME_GRAVITY;
	this -> x = x;
	this -> y = y;
	this -> direction = direction;
	state = ID_RUNNING_FLAME_1;
	birth_time = GetTickCount64();
}

void RFlame::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x -  RFLAME_BBOX_WIDTH/ 2;
	top = y - RFLAME_BBOX_HEIGHT / 2;
	right = left + RFLAME_BBOX_WIDTH;
	bottom = top + RFLAME_BBOX_HEIGHT;
}

void RFlame::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if(GetTickCount64() > birth_time + 5000) Delete();
	if(direction == 0) vx = RFLAME_WALKING_SPEED;
	else vx = -RFLAME_WALKING_SPEED;
	if (GetTickCount64() - last_change_time > 250) {
		state++;
		if(state > 79004) state = 79002;
		last_change_time = GetTickCount64();
	}
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void RFlame::OnCollisionWith(LPCOLLISIONEVENT e)
{ 
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<RFlame*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		direction = !direction;
	}
}
void RFlame::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void RFlame::Render()
{
	int aniId = state;
	if(direction == 0) aniId += 100;
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);


	if (ani != NULL) {
		ani->Render(x, y);
	}
	else {

		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
	}

	RenderBoundingBox();
}

void RFlame::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case ID_RUNNING_FLAME_1:
		break;
	case ID_RUNNING_FLAME_2:
		break;
	case ID_RUNNING_FLAME_3:
		break;
	case ID_RUNNING_FLAME_4:
		break;
	}
}