#include "GameObject.h"

#define RFLAME_BBOX_WIDTH 16
#define RFLAME_BBOX_HEIGHT 14

#define RFLAME_WALKING_SPEED 0.05f
#define RFLAME_GRAVITY 0.002f

#define ID_RUNNING_FLAME_1 79001
#define ID_RUNNING_FLAME_2 79002
#define ID_RUNNING_FLAME_3 79003
#define ID_RUNNING_FLAME_4 79004



class RFlame : public CGameObject
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
	RFlame(float x, float y, bool direction);
	virtual void SetState(int state);
};

