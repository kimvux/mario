#include "Tunnel.h"

void Tunnel::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani_id)->Render(x, y);
	//RenderBoundingBox();
}

void Tunnel::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	t = y - height / 2;
	r = l + width;
	b = t + height;
}
void Tunnel::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
}