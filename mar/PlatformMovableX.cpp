#include "PlatformMovableX.h"

void PlatformMovableX::Render()
{
	this->CPlatform::Render();
}

void PlatformMovableX::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Move the platform
	x += moveDirection * moveSpeed * dt;
	// Check if the platform has reached the end of its movement range
	if (x > startX + moveRange)
	{
		x = startX + moveRange; // Clamp to the right edge
		moveDirection = -1; // Change direction to left
	}
	else if (x < startX - moveRange)
	{
		x = startX - moveRange; // Clamp to the left edge
		moveDirection = 1; // Change direction to right
	}
}