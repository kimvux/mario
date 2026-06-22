#include "Text.h"
#include "Game.h"
#include "Mario.h"
#include "PlayScene.h"
#include "debug.h"
#include <cctype>

Text::Text(float x, float y, int type, string text) : CGameObject(x, y) {
    this->type = type;
    this->text = text;
    cameraX = x;
    cameraY = y;
}

void Text::GetBoundingBox(float &l, float &t, float &r, float &b){

    l = x;
    r = l;
    if (type == TEXT_TYPE_NUMBER) {
        t = y - NUMBER_HEIGHT / 2;
        b = y + NUMBER_HEIGHT / 2;
    } else {
        t = y - TEXT_HEIGHT / 2;
        b = y + TEXT_HEIGHT / 2;
    }
}

void Text::Render() {
    CSprites * s = CSprites::GetInstance();
    switch (type) {
        case TEXT_TYPE_LETTER:{
            for (int i = 0; i < text.size(); i++) {
                int offsetX = i * CHAR_WIDTH - text.size() * CHAR_WIDTH / 2 + 3 * (i - text.size() / 2);
                s->Get(static_cast<int>(tolower(text[i])))->Draw(x + offsetX, y);
            }
            break;
        }
       
        case TEXT_TYPE_SCORE: {
            LPGAME game = CGame::GetInstance();
            CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
            int score = game->TotalScore + mario->score;
            
            string scoreStr = to_string(score);
            for (int i = 0; i < scoreStr.size(); i++) {
                int offsetX = i * CHAR_WIDTH - scoreStr.size() * CHAR_WIDTH / 2 + 3 * (i - scoreStr.size() / 2);
                s->Get(static_cast<int>(scoreStr[i]))->Draw(x + offsetX, y);
            }
            break;
        }
        
        case TEXT_TYPE_COIN: {
            LPGAME game = CGame::GetInstance();
            CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
            int coin = mario->coin;

            string coinStr = to_string(coin);
            for (int i = 0; i < coinStr.size(); i++) {
                int offsetX = i * CHAR_WIDTH - coinStr.size() * CHAR_WIDTH / 2 + 3 * (i - coinStr.size() / 2);
                s->Get(static_cast<int>(coinStr[i]))->Draw(x + offsetX, y);
            }
            break;
        }
        
        case TEXT_TYPE_TIME: {
            // dont have yet
            break;
        }

        case TEXT_TYPE_NUMBER: {
            for (int i = 0; i < text.size(); i++) {
                int offsetX = i * CHAR_WIDTH - text.size() * CHAR_WIDTH / 2 + 3 * (i - text.size() / 2);
                s->Get(static_cast<int>(text[i]))->Draw(x + offsetX, y);
            }
            break;
        }
    }
}

void Text::Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects) {
    float cam_x, cam_y;
    CGame::GetInstance()->GetCamPos(cam_x, cam_y);
    targetX = cam_x + cameraX;
    targetY = cam_y + cameraY;
    float vx = (targetX - x) / 60;
    float vy = (targetY - y) / 60;
    x += vx * dt;
    y += vy * dt;
}