#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
protected:
	float width;
	float height;
	int ani_id;
public:
	CBrick(float x, float y, float width, float height, int ani_id) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->ani_id = ani_id;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};