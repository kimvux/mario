#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CBrick : public CGameObject {
protected:
	float width;
	float height;
	int ani_id;
	float defaultY;
	int boundtime;
public:
	CBrick(float x, float y, float width, float height, int boundtime, int ani_id) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->ani_id = ani_id;
		this->defaultY = y;
		this->boundtime = boundtime;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void boundUp();
};