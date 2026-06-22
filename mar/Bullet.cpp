#include "Bullet.h"
#include "Brick.h"
#include "Mario.h"


CBullet::CBullet(float x, float y, int direction) :CGameObject(x, y) {
	this->ax = 0;
	this->ay = BULLET_GRAVITY;
	this->direction = direction;
	SetState(BULLET_STATE_FLYING);
	isCollided = false;
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

void CBullet::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case BULLET_STATE_FLYING:
		switch (direction) {
			case 1: 
				vy = BULLET_FLYING_SPEED;
				break;
			case 2:
				vx = -BULLET_FLYING_SPEED;
				break;
			case 3:
				vy = -BULLET_FLYING_SPEED;
				break;
			case 4: 
				vx = BULLET_FLYING_SPEED;
				break;
		}
		break;
	}

}
void CBullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CBrick*>(e->obj)) Delete();
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBullet*>(e->obj)) return;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	y += vy * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::Render() {
	int aniId;
	if(direction == 2 || direction == 4) aniId = 6000;
	else aniId = 6001;
	float s ;
	if(direction == 1 || direction == 4) s = -1;
	else s = 1;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y, s);
	//RenderBoundingBox();
}