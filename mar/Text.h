#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include <string>
#define TEXT_TYPE_LETTER 1
#define TEXT_TYPE_INSCENESCORE 2
#define TEXT_TYPE_COIN 3
#define TEXT_TYPE_TIME 4
#define TEXT_TYPE_NUMBER 5
#define TEXT_TYPE_TOTALSCORE 6
#define TEXT_TYPE_NEXTSCENE 7
#define TEXT_TYPE_LIVES 8

#define CHAR_WIDTH 13
#define TEXT_HEIGHT 13
#define NUMBER_HEIGHT 11

class Text : public CGameObject
{
protected:
    string text;
    int type;
    float cameraX;  
    float cameraY;
    float targetX;
    float targetY;
    int preTotalScore;
public:
    Text(float x, float y, int type, string text = "");
    void Render();
    void Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects);
    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }
    void GetBoundingBox(float& l, float& t, float& r, float& b);
};

