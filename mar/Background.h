#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BACKGROUND 700000

class CBackground : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;				// Unit: cell
	float cellWidth;
	float cellHeight;
	int ani_id;
	float z;
	float scale;
	float ax = 0.0f;
public:
	CBackground(float x, float y, float z, float cell_width, float cell_height, int length, int height, int ani_id, float scale = 1.0f) : CGameObject(x, y) { 
		this->ani_id = ani_id;
		this->z = z;
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->scale = scale;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {}
};