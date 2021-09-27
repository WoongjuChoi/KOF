#include "BattleManager.h"

void BattleManager::Init()
{
    player1.HP = 100;
    player2.HP = 100;

    player1.isLose = false;
    player1.isWin = false;
    player2.isLose = false;
    player2.isWin = false;

    isHit = false;

    pos.x = pos.y = 0;

    for (int i = 0; i < 5; i++)
    {
        SetHitBoxPos(i, 0, 0, 0, 0, ePlayer::player1, pos);
    }

    for (int i = 0; i < 5; i++)
    {
        SetHitBoxPos(i, 0, 0, 0, 0, ePlayer::player2, pos);
    }
}

void BattleManager::Render(HDC hdc)
{
    for (int i = 0; i < 5; i++) 
    {
        MoveToEx(hdc, player1.hitBox[i].left, player1.hitBox[i].top, NULL);
        LineTo(hdc, player1.hitBox[i].left, player1.hitBox[i].bottom);
        LineTo(hdc, player1.hitBox[i].right, player1.hitBox[i].bottom);
        LineTo(hdc, player1.hitBox[i].right, player1.hitBox[i].top);
        LineTo(hdc, player1.hitBox[i].left, player1.hitBox[i].top);
    }

    for (int i = 0; i < 5; i++)
    {
        MoveToEx(hdc, player2.hitBox[i].left, player2.hitBox[i].top, NULL);
        LineTo(hdc, player2.hitBox[i].left, player2.hitBox[i].bottom);
        LineTo(hdc, player2.hitBox[i].right, player2.hitBox[i].bottom);
        LineTo(hdc, player2.hitBox[i].right, player2.hitBox[i].top);
        LineTo(hdc, player2.hitBox[i].left, player2.hitBox[i].top);
    }
}

void BattleManager::SetHitBoxPos(int hitboxNum, int left, int top, int right, int bottom, ePlayer player, POINTFLOAT pos)
{
	switch (player)
	{
    case ePlayer::player1:
        player1.hitBox[hitboxNum].left = pos.x - right;
        player1.hitBox[hitboxNum].top = pos.y - top;
        player1.hitBox[hitboxNum].right = pos.x + left;
        player1.hitBox[hitboxNum].bottom = pos.y + bottom;
        break;
    case ePlayer::player2:
        player2.hitBox[hitboxNum].left = pos.x - left;
        player2.hitBox[hitboxNum].top = pos.y - top;
        player2.hitBox[hitboxNum].right = pos.x + right;
        player2.hitBox[hitboxNum].bottom = pos.y + bottom;
        break;
	}
}

bool BattleManager::Hit()
{
    for (int i = 1; i < 5; i++)
    {
        if (IntersectRect(&tempRect, &player1.hitBox[i], &player2.hitBox[0]) && !isHit)
        {
            isHit = true;
            player2.HP -= damage;

            if (player2.HP <= 0)
            {
                player2.isLose = true;
                player1.isWin = true;
            }

            return true;
        }
    }

    for (int i = 1; i < 5; i++)
    {
        if (IntersectRect(&tempRect, &player2.hitBox[i], &player1.hitBox[0]) && !isHit)
        {
            isHit = true;
            player1.HP -= damage;

            if (player1.HP <= 0)
            {
                player1.isLose = true;
                player2.isWin = true;
            }

            return true;
        }
    }

    return false;
}
