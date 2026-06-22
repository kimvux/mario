#include "Bowser.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Bullet.h"
#include "RFlame.h"


void CBowser::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BOWSER_BBOX_WIDTH / 2;
	top = y - BOWSER_BBOX_HEIGHT / 2;
	right = left + BOWSER_BBOX_WIDTH;
	bottom = top + BOWSER_BBOX_HEIGHT;
}

void CBowser::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {	
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
	else {
		if (isShooting) {
			vx = 0;
			vy = 0;

			if (GetTickCount64() - last_attack > shootTime)
			{
				isShooting = false;
			}
		}
		else {
			if (GetTickCount64() - last_change_time > change_time) {
				if (state < 77004) state++;
				else state = 77001;
				last_change_time = GetTickCount64();
			}
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
	}
	if (GetTickCount64() - last_attack > Attack_Time) {
		srand((unsigned)time(nullptr));
		int random_num = rand();
		random_num %= 3;
		if (random_num == 0) {
			BreathFlame();
		}
		else if (random_num == 1) {
			Crashing();
		}
		else if (random_num == 2) {
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

	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);

	if (ani != NULL) {
		ani->Render(x, y, 0.25f);
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
	isCrashing = 1;
	last_attack = GetTickCount64();
}

void CBowser::Shooting()
{
	isShooting = 1;
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

void CBowser::BreathFlame()
{
	RFlame* flame1 = new RFlame(x, y, 1);
	RFlame* flame2 = new RFlame(x, y, 0);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	scene->AddObject(flame1);
	scene->AddObject(flame2);
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