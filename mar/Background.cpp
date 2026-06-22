#include "Background.h"
#include "Mario.h"
#include "PlayScene.h"
#include "debug.h"

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	for (int j = 0; j < this->height; j++)
	{
		for (int i = 0; i < this->length; i++)
		{
			animations->Get(ani_id)->Render(x + i * cellWidth, y + j * cellHeight, scale);
		}
	}
}
void CBackground::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += dt * moveY / 100;
	if (y > 450 + cellHeight / 2 && moveY > 0) {
		y = 2 - cellHeight / 2;
	}
	if (y < 0 - cellHeight / 2 && moveY < 0) {
		y = 450 + cellHeight / 2;
	}
	if (z == 0) return;
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (!mario) return;
	if (mario->getVx() == 0) return;
	switch (mario->GetState()) {
	case MARIO_STATE_WALKING_RIGHT: {
		ax = -(MARIO_ACCEL_WALK_X + z / 100);
		break;
	}
	case MARIO_STATE_WALKING_LEFT: {
		ax = (MARIO_ACCEL_WALK_X + z / 100);
		break;
	}
	default: {
		ax = 0.0f;
		break;
	}
	}
	x += ax * dt;
}