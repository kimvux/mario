#include "GameObject.h"

#define FFLAME_BBOX_WIDTH 16
#define FFLAME_BBOX_HEIGHT 14

#define FFLAME_FLYING_SPEED 0.05f
#define FFLAME_GRAVITY 0

#define ID_FLYING_FLAME_1 81001
#define ID_FLYING_FLAME_2 81002



class FFlame : public CGameObject
{
protected:
	float ax;
	float ay;
	bool direction;
	int state;
	ULONGLONG last_change_time;
	ULONGLONG birth_time;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();


	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	FFlame(float x, float y, bool direction);
	virtual void SetState(int state);
};

