#pragma once
#include "Platform.h"
class PlatformMovableX : public CPlatform
{
protected:
	float moveRange;
	float moveSpeed;
	int moveDirection; // 1: right, -1: left
	float startX;
public:
	PlatformMovableX(float x, float y, float cell_width, float cell_height, int length, int height, int sprite_id, float move_range, float move_speed, int moveDirection) : CPlatform(x, y, cell_width, cell_height, length, height, sprite_id)
	{
		this->moveRange = move_range;
		this->moveSpeed = move_speed;
		this->moveDirection = moveDirection;
		this->startX = x;
	};
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	float GetMoveAndSpeed() { return moveSpeed * moveDirection; }
};

