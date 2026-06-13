#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class Tunnel : public CGameObject {
protected:
	float width;
	float height;
	int ani_id;
	int targetScene;
public:
	Tunnel(float x, float y, float width, float height,int targetScene, int ani_id) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->ani_id = ani_id;
		this->targetScene = targetScene;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetTargetScene() { return targetScene; }
};