#include "Star.h"

void CSTAR::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_STAR)->Render(x, y);

	//RenderBoundingBox();
}

void CSTAR::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - STAR_BBOX_WIDTH / 2;
	t = y - STAR_BBOX_HEIGHT / 2;
	r = l + STAR_BBOX_WIDTH;
	b = t + STAR_BBOX_HEIGHT;
}
void CSTAR::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if(isGrowUp){
		GrowUp(dt);
		return;
	}
	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CSTAR::GrowUp(DWORD dt) {
	y -= dt/16;
	if(y <= defaultY) {
		isGrowUp = false;
		y = defaultY;
		vx = 0.05f;
	}
}
void CSTAR::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}
void CSTAR::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSTAR*>(e->obj)) return;

	if (e->ny < 0)
	{
		vy = -0.3f;
		ay = 0.001f;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}