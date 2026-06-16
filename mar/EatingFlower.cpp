#include "EatingFlower.h"
#include "PlayScene.h"
#include "Bullet.h"

CFlower::CFlower(float x, float y) : CGameObject(x, y) {
	this->vx = 0;
	this->vy = 0;
	this->IsOpen = false;
	this->lastBiteTime = GetTickCount64();
	SetState(FLOWER_STATE_CLOSED_MOUTH);
}

void CFlower::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - FLOWER_BBOX_WIDTH / 2;
	top = y - FLOWER_BBOX_HEIGHT / 2;
	right = left + FLOWER_BBOX_WIDTH;
	bottom = top + FLOWER_BBOX_HEIGHT;
}

void CFlower::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case FLOWER_STATE_OPEN_MOUTH:
		break;
	case FLOWER_STATE_CLOSED_MOUTH:
		break;
	}

}

void CFlower::OnNoCollision(DWORD dt)
{

};

void CFlower::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBullet*>(e->obj)) return;
}

void CFlower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	if (GetTickCount64() - lastBiteTime > coolDown)
	{
		if (IsOpen) {
			SetState(FLOWER_STATE_CLOSED_MOUTH);
			IsOpen = false;
		}
		else {
			SetState(FLOWER_STATE_OPEN_MOUTH);
			IsOpen = true;
		}
		lastBiteTime = GetTickCount64();
	}
}
void CFlower::Render() {
	int aniId = (IsOpen) ? ID_ANI_FLOWER_OPEN : ID_ANI_FLOWER_CLOSED;

	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);

	if (ani != NULL) {
		ani->Render(x, y);
	}
	else {

		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
	}

	RenderBoundingBox();
}