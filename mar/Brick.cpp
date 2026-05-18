#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani_id)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - width/2;
	t = y - height/2;
	r = l + width;
	b = t + height;
}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (y >= defaultY) {
		y = defaultY;
		return;
	}
	y += 0.08 * dt;
}
void CBrick::boundUp() {
	if (!boundtime) return;
	boundtime--;
	this->y -= height / 2;
}