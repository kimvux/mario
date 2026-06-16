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
	bool deleteAfterBound;
	int spawnType;
public:
	CBrick(float x, float y, float width, float height, int boundtime, int ani_id, bool deleteAfterBound, int spawnType) : CGameObject(x, y) {
		this->width = width;
		this->height = height;
		this->ani_id = ani_id;
		this->defaultY = y;
		this->boundtime = boundtime;
		this->deleteAfterBound = deleteAfterBound;
		this->spawnType = spawnType;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void boundUp();
	bool isDeleteAfterBound() { return deleteAfterBound; }
};