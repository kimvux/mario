#include "FFlame.h"
#include "PlayScene.h"

FFlame::FFlame(float x, float y) {
	this->ax = 0;
	this->ay = 0; 
	this->vx = 0.05f; 
	this->vy = -0.05f;
	this->x = x;
	this->y = y;

	state = ID_FLYING_FLAME_1;
	birth_time = GetTickCount64();
}

void FFlame::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FFLAME_BBOX_WIDTH / 2;
	top = y - FFLAME_BBOX_HEIGHT / 2;
	right = left + FFLAME_BBOX_WIDTH;
	bottom = top + FFLAME_BBOX_HEIGHT;
}

void FFlame::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (GetTickCount64() > birth_time + 10000) Delete();
	if (GetTickCount64() > last_change_direction) {
		srand((unsigned)time(nullptr));
		vx = ((rand() % 100) / 100.0f) * 0.3f - 0.15f;
		vy = ((rand() % 100) / 100.0f) * 0.3f - 0.15f;

		last_change_direction = GetTickCount64();
	}

	if (GetTickCount64() - last_change_time > 250) {
		state++;
		if (state > 81002) state = 81001;
		last_change_time = GetTickCount64();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FFlame::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<FFlame*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		direction = !direction;
	}
}
void FFlame::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void FFlame::Render()
{
	int aniId = state;
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);


	if (ani != NULL) {
		ani->Render(x, y);
	}
	else {

		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
	}

	RenderBoundingBox();
}

void FFlame::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case ID_FLYING_FLAME_1:
		break;
	case ID_FLYING_FLAME_2:
		break;
	}
}