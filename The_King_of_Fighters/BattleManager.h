#pragma once
#include "Config.h"
#include "Singleton.h"

struct Player
{
    int HP;
    RECT hitBox[5]; // 0 : 플레이어 1 : 약손 2 : 강손 3 : 약발 4 : 강발
    bool isLose;
    bool isWin;
};

class BattleManager : public Singleton<BattleManager>
{
protected:
    int damage;
    bool isHit;
    Player player1;
    Player player2;
    POINTFLOAT pos;
    RECT tempRect; // 네모 교집합 확인용

public:
    void Init(); // 히트박스들 위치 초기화
    void Render(HDC hdc);
    void SetHitBoxPos(int hitboxNum, int left, int top, int right, int bottom, ePlayer player, POINTFLOAT pos);
    bool Hit();

    inline void SetIsHit(bool hit) { this->isHit = hit; }
    inline void SetDamage(int damage) { this->damage = damage; }
    inline int Getplayer1Hp() { return player1.HP; }
    inline int Getplayer2Hp() { return player2.HP; }
    inline bool Getplayer1Win() { return player1.isWin; }
    inline bool Getplayer2Win() { return player2.isWin; }
    inline bool Getplayer1Lose() { return player1.isLose; }
    inline bool Getplayer2Lose() { return player2.isLose; }
};

