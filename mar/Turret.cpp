#include "Turret.h"
#include "PlayScene.h"
#include "Bullet.h"

CTurret::CTurret(float x, float y, int dir) : CGameObject(x, y) {
	this->dir = dir;
	this->vx = 0;
	this->vy = 0;
}

void CTurret::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - TURRET_BBOX_WIDTH / 2;
	top = y - TURRET_BBOX_HEIGHT / 2;
	right = left + TURRET_BBOX_WIDTH;
	bottom = top + TURRET_BBOX_HEIGHT;
}
 
void CTurret::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case TURRET_STATE_NORMAL:
		
		break;
	}
}

void CTurret::OnNoCollision(DWORD dt)
{
	
};

void CTurret::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CTurret::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	if (GetTickCount64() - lastShotTime > coolDown)
	{
		SpawnBullet();

		lastShotTime = GetTickCount64();
	}
}

void CTurret::SpawnBullet()
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CBullet* b = NULL; 

	switch (dir) {
	case 1: 
		b = new CBullet(this->x - 10, this->y - 6, false);
		scene->AddObject(b);
		break;
	case 2: 
		b = new CBullet(this->x + 10, this->y - 6, true);
		scene->AddObject(b);
		break;
	case 3: 
		CBullet * bLeft = new CBullet(this->x - 10, this->y - 6, false);
		CBullet* bRight = new CBullet(this->x + 10, this->y - 6, true);
		scene->AddObject(bLeft);
		scene->AddObject(bRight);
		break;
	}
}

void CTurret::Render() {
	int aniId = TURRET_STATE_NORMAL;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}