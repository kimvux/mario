#include "Bullet.h"


CBullet::CBullet(float x, float y, bool isRight) :CGameObject(x, y) {
	this->ax = 0;
	this->ay = BULLET_GRAVITY;
	this->isRight = isRight;
	SetState(BULLET_STATE_FLYING);
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
		if (!isRight)
			vx = -BULLET_FLYING_SPEED;
		else vx = BULLET_FLYING_SPEED;
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
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBullet*>(e->obj)) return;


}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	x += vx * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::Render() {
	int aniId = 6000;
	float s = isRight ? 1.0f : -1.0f;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y, -s);
	RenderBoundingBox();
}