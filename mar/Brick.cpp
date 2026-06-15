#include "Brick.h"
#include "AssetIDs.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "SoundManager.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani_id)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - width/2;
	t = y - height/2;
	r = l + width;
	b = t + height;
}
void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (y >= defaultY) {
		y = defaultY;
		if (boundtime == 0 && deleteAfterBound) Delete();
		if (boundtime == 0 && !deleteAfterBound && (ani_id == 200001 || ani_id == 200002)) ani_id = 200003;
		return;
	}
	y += 0.08 * dt;
}
void CBrick::boundUp() {
	if (!boundtime) return;
	boundtime--;
	this->y -= height / 2;
	switch (spawnType)
	{
	case 0:
		break;

	case OBJECT_TYPE_COIN: 
	{
		SoundManager::GetInstance()->PlaySFX(L"coin");
		CCoin* c = new CCoin(x, y - height / 2);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(c);
		CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->addCoin(1);
		c->Delete();
		break;
	}

	case OBJECT_TYPE_MUSHROOM:
	{
		Mushroom* m = new Mushroom(x, y);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(m);
		break;
	}

	case OBJECT_TYPE_STAR:
	{
		CSTAR* s = new CSTAR(x, y);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		scene->AddObject(s);
		break;
	}
	}
}