#include "Bowser.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Bullet.h"
#include "RFlame.h"
#include "FFlame.h"


void CBowser::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BOWSER_BBOX_WIDTH / 2;
	top = y - BOWSER_BBOX_HEIGHT / 2;
	right = left + BOWSER_BBOX_WIDTH;
	bottom = top + BOWSER_BBOX_HEIGHT;
}

void CBowser::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {		
	if (isAttacking) {
		if (isCrashing) {
			if (GetTickCount64() - last_attack < 1000) {
				vx = direction * CrashingSpeed * 0.05;
				vy = 0;
			}
			else {
				vx = -direction * CrashingSpeed;
				vy = 0;

				if (GetTickCount64() - last_attack > CrashingTime)
				{
					isCrashing = false;
					vx = vx / 2;
				}
			}
		}
		if (isShooting) {
			vx = 0;
			vy = 0;
			if (GetTickCount64() - last_shot > 2000) {
				ShootAgain();
			}

			if (GetTickCount64() - last_attack > shootTime) {
				isShooting = false;
			}
		}
		if (isBreathingFlame) {
			vx = 0;
			vy = 0;
			if (GetTickCount64() - last_attack > breathTime)
				isBreathingFlame = false;
		}
			
	}
	if(!isAttacking){
		if (GetTickCount64() - last_change_time > change_time) {
			if (state < 77004) state++;
			else state = 77001;
			last_change_time = GetTickCount64();
		}
	}
	if(!isCrashing){
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		LPGAMEOBJECT mario = scene->GetPlayer();
		if (mario != NULL) {
			float m_x, m_y;
			mario->GetPosition(m_x, m_y);
			if (abs(m_x - this->x) > 30)
				if (m_x < this->x) {
					vx = -BOWSER_WALKING_SPEED;
					direction = 1;
				}
				else {
					vx = BOWSER_WALKING_SPEED;
					direction = -1;
				}
		}
	}
	if (GetTickCount64() - last_attack > Attack_Time) {
		srand((unsigned)time(nullptr));
		int random_num = rand();
		random_num %= 3;
		isAttacking = 1;
		if (random_num == 0) {
			isBreathingFlame = 1;
			BreathFlame();
		}
		else if (random_num == 1) {
			isCrashing = 1;
			Crashing();
		}
		else if (random_num == 2) {
			isShooting = 1;
			Shooting();
		}
	}
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBowser::Render()
{
	int aniId = state;
	if(direction == -1) aniId  += 1000;

	if(isBreathingFlame) aniId = BOWSER_STATE_BREATH;
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);

	if (ani != NULL) {
		float scale;
		if(isBreathingFlame) scale = 0.095f;
		else scale = 0.25;
		ani->Render(x, y, scale);
	}
	else {

		DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
	}

	RenderBoundingBox();
}

void CBowser::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case BOWSER_STATE_WALKING_1:
		break;
	case BOWSER_STATE_WALKING_2:
		break;
	case BOWSER_STATE_WALKING_3:
		break;
	case BOWSER_STATE_WALKING_4:
		break;
	}

}

void CBowser::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CBowser::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CBowser*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
}

void CBowser::Crashing()
{
	last_attack = GetTickCount64();
}

void CBowser::Shooting()
{
	last_shot = GetTickCount64();
	CBullet* Bullet1 = new CBullet(x + 80, y - 500, 1);
	CBullet* Bullet2 = new CBullet(x - 90, y, 3);
	CBullet* Bullet3 = new CBullet(x + 75, y, 3);
	CBullet* Bullet4 = new CBullet(x - 95, y - 500, 1);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(Bullet1);
	scene->AddObject(Bullet2);
	scene->AddObject(Bullet3);
	scene->AddObject(Bullet4);
	last_attack = GetTickCount64();
}

void CBowser::ShootAgain()
{
	last_shot = GetTickCount64();
	CBullet* Bullet1 = new CBullet(x + 80, y - 500, 1);
	CBullet* Bullet2 = new CBullet(x - 90, y, 3);
	CBullet* Bullet3 = new CBullet(x + 75, y, 3);
	CBullet* Bullet4 = new CBullet(x - 95, y - 500, 1);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(Bullet1);
	scene->AddObject(Bullet2);
	scene->AddObject(Bullet3);
	scene->AddObject(Bullet4);
}

void CBowser::BreathFlame()
{
	RFlame* flame1 = new RFlame(x, y -10, 1);
	RFlame* flame2 = new RFlame(x, y - 10, 0);
	FFlame* flame3 = new FFlame(x, y - 10);
	FFlame* flame4 = new FFlame(x, y - 10);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(flame1);
	scene->AddObject(flame2);
	scene->AddObject(flame3);
	scene->AddObject(flame4);
	last_attack = GetTickCount64();
}



void CBowser::takeDmg()
{
	hp--;
}
int CBowser::GetHp()
{
	return hp;
}