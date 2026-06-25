#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define POPUP_SCORE_DISAPPEAR_TIME 1
#define POPUP_SCORE_BBOX_WIDTH 8
#define POPUP_SCORE_BBOX_HEIGHT 8
class PopUpScore : public CGameObject
{
protected:
    int score;
    DWORD timerStart; 
public:
    PopUpScore(float x, float y, int score);
    void Render();
    void Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects);
    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }
    void GetBoundingBox(float& l, float& t, float& r, float& b);
};

