#include "Turtle.h"
#include "Brick.h"

Turtle::Turtle(float x, float y, float left, float right) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = TURTLE_GRAVITY;
	this->left = left;
	this->right = right;
	this->vx = -TURTLE_WALKING_SPEED;
	isDie = false;
	isSlide = false;
	timeSlide = 0;
	timeSlideStartSet = false;
}

void Turtle::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDie)
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT_DIE / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - TURTLE_BBOX_WIDTH / 2;
		top = y - TURTLE_BBOX_HEIGHT / 2;
		right = left + TURTLE_BBOX_WIDTH;
		bottom = top + TURTLE_BBOX_HEIGHT;
	}
}

void Turtle::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Turtle::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<Turtle*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (dynamic_cast<CBrick*>(e->obj) && isSlide) {
			CBrick* br = dynamic_cast<CBrick*>(e->obj);
			if (br->isDeleteAfterBound()) {
				br->boundUp();
			}
		}
		vx = -vx;
	}
}

void Turtle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (timeSlide >= TIMEOUT_SLIDE) {
		isSlide = true;
	}
	timeSlide += timeSlideStartSet ? dt : 0;

	vy += ay * dt;
	vx += ax * dt;

	if (x < left && !isDie)
	{
		x = left;
		vx = -vx;
	}
	else if (x > right && !isDie)
	{
		x = right;
		vx = -vx;
	}

	if (isDie && y > 500)
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void Turtle::Render()
{
	int aniId;
	if (vx > 0) aniId = ID_ANI_TURTLE_WALKING_FLIP;
	if (vx <= 0) aniId = ID_ANI_TURTLE_WALKING;
	if (isDie)	aniId = ID_ANI_TURTLE_DIE;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void Turtle::Kill()
{
	y -= (TURTLE_BBOX_HEIGHT - TURTLE_BBOX_HEIGHT_DIE) / 2;
	vx = 0;
	isDie = true;
}

void Turtle::slide(float direction)
{
	y -= 2;
	vx = direction * TURTLE_SLIDE_SPEED;
	timeSlideStartSet = true;
}
