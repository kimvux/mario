#include "PopUpScore.h"

PopUpScore::PopUpScore(float x, float y, int score) : CGameObject(x, y)
{
    this->score = score;
    timerStart = GetTickCount64();
}

void PopUpScore::Render(){
    CSprites::GetInstance()->Get(score)->Draw(x, y);
}


void PopUpScore::Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects){
    if (POPUP_SCORE_DISAPPEAR_TIME - (GetTickCount64() - timerStart) / 1000 <= 0) this->Delete();
    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void PopUpScore::GetBoundingBox(float& l, float& t, float& r, float& b){
    l = x - POPUP_SCORE_BBOX_WIDTH / 2;
    t = y - POPUP_SCORE_BBOX_HEIGHT / 2;
    r = l + POPUP_SCORE_BBOX_WIDTH;
    b = t + POPUP_SCORE_BBOX_HEIGHT;
}
