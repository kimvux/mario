#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16
#define ID_ANI_BRICK 0

class Brick : public CGameObject
{
public:
	Brick(float x, float y) : CGameObject(x, y) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
};

