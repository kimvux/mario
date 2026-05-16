#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
// 
// The most popular type of object in Mario! 
// 
class CPlatform : public CGameObject
{
protected:
	int length;				// Unit: cell 
	int height;				// Unit: cell
	float cellWidth;
	float cellHeight;
	int spriteId;

public:
	CPlatform(float x, float y, float cell_width, float cell_height, int length, int height, int sprite_id) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteId = sprite_id;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();

	int IsDirectionColliable(float nx, float ny);
};

typedef CPlatform* LPPLATFORM;