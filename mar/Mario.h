#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"
#include <Windows.h>

#include "debug.h"

#define MARIO_WALKING_SPEED		0.15f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_DASH			650


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// UNTOUCHABLE
#define ID_ANI_MARIO_UNTOUCHABLE_IDLE_RIGHT 1700
#define ID_ANI_MARIO_UNTOUCHABLE_IDLE_LEFT 1701

#define ID_ANI_MARIO_UNTOUCHABLE_JUMP_RIGHT 1704
#define ID_ANI_MARIO_UNTOUCHABLE_JUMP_LEFT 1705

#define ID_ANI_MARIO_UNTOUCHABLE_WALK_RIGHT 1702
#define ID_ANI_MARIO_UNTOUCHABLE_WALK_LEFT 1703

#define ID_ANI_MARIO_UNTOUCHABLE_JUMP_WALK_RIGHT 1706
#define ID_ANI_MARIO_UNTOUCHABLE_JUMP_WALK_LEFT 1707

#define ID_ANI_MARIO_UNTOUCHABLE_SIT_RIGHT 1708
#define ID_ANI_MARIO_UNTOUCHABLE_SIT_LEFT 1709

#define ID_ANI_MARIO_UNTOUCHABLE_BRACE_RIGHT 1710
#define ID_ANI_MARIO_UNTOUCHABLE_BRACE_LEFT 1711

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_UNTOUCHABLE	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 10000
#define MARIO_RECOVERY_TIME 2000
#define MARIO_TUNNEL_TIME 1000

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin;
	bool moveAble;
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithStar(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithTurtle(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithHammer(LPCOLLISIONEVENT e);
	void OnCollisionWithSpikeTurtle(LPCOLLISIONEVENT e);

	float tunnelTimer = 0;
	bool isOnTunnel = false;
	int tunnelSceneId = 0;
	bool isChangingScene = false;
	float tunnelStartY = 0;

	bool isOnMovingPlatform = false;
	float platformVx = 0;
	float platformVy = 0;

	int recovery;
	float recoveryStart;

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdUntouchable();

public:
	CMario(float x, float y, bool moveAble) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		this->moveAble = moveAble;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		recovery = 0;
		recoveryStart = -1;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartRecovery() { recovery = 1; recoveryStart = GetTickCount64(); }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	float getVx() { return vx; }
	bool isDashing = false;
	int dashDirection = 0;
	bool IsChangingScene() { return isChangingScene; }
	void addCoin(int x) { coin += x; }
	void getHitByHammer();
};