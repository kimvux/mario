#include "PlatformMovableY.h"

void PlatformMovableY::Render()
{
	this->CPlatform::Render();
}

void PlatformMovableY::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += moveDirection * moveSpeed * dt;

	if (y > startY + moveRange && moveRange != 0) // Danger: easy to flict through platform
	{
		y = startY + moveRange;
		moveDirection = -1;
	}
	else if (y < startY - moveRange && moveRange != 0) // Danger: easy to flict through platform
	{
		y = startY - moveRange;
		moveDirection = 1;
	}
	if (y > 450 && moveRange == 0) {
		y = 0;
	}
	if (y < 0 && moveRange == 0) {
		y = 450;
	}
}