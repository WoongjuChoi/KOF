#include "King.h"
#include "Image.h"
#include "KeyManager.h"
#include "BattleManager.h"

void King::Init(ePlayer p)
{
	SetKey(p);
	player = p;

	// 킹 이미지 초기화
	img = new Image[eActs::end];
	img[eActs::standing].Init("Image/King/King_Standing.bmp", 3720, 576, 8, 1, true, RGB(255, 0, 255));
	img[eActs::moveForward].Init("Image/King/King_MoveFoward.bmp", 4650, 576, 10, 1, true, RGB(255, 0, 255));
	img[eActs::moveBackward].Init("Image/King/King_MoveBackward.bmp", 4650, 576, 10, 1, true, RGB(255, 0, 255));
	img[eActs::weekPunch].Init("Image/King/King_WeakPunch.bmp", 3255, 576, 7, 1, true, RGB(255, 0, 255));
	img[eActs::weekFoot].Init("Image/King/King_WeakKick.bmp", 3720, 576, 8, 1, true, RGB(255, 0, 255));
	img[eActs::strongPunch].Init("Image/King/King_StrongPunch.bmp", 5115, 576, 11, 1, true, RGB(255, 0, 255));
	img[eActs::strongFoot].Init("Image/King/King_StrongKick.bmp", 6975, 576, 15, 1, true, RGB(255, 0, 255));
	img[eActs::hit].Init("Image/King/King_Attacked.bmp", 1395, 576, 3, 1, true, RGB(255, 0, 255));
	img[eActs::victory].Init("Image/King/King_Victory.bmp", 3255, 576, 7, 1, true, RGB(255, 0, 255));
	img[eActs::die].Init("Image/King/King_Defeat.bmp", 5580, 576, 12, 1, true, RGB(255, 0, 255));

	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 8;
	frameRate = 5;
	action = eActs::standing;
	moveSpeed = 10.0f;
	delay = false;

	if (player == ePlayer::player1)
	{
		pos.x = WIN_SIZE_X / 4;
	}
	else
	{
		pos.x = WIN_SIZE_X / 4 * 3;
	}
	pos.y = WIN_SIZE_Y / 4 * 3 + 50;

	kingSize.x = 45;
	kingSize.y = 220;

	punchPos.x = pos.x;
	punchPos.y = pos.y - kingSize.y * 3 / 4;
	
	kickPos.x = pos.x;
	kickPos.y = pos.y - kingSize.y / 2;
}

void King::Update()
{
	punchPos.x = pos.x;
	kickPos.x = pos.x;

	BattleManager::GetSingleton()->SetHitBoxPos(0, kingSize.x, kingSize.y, kingSize.x, 0, player, pos);
	BattleManager::GetSingleton()->SetHitBoxPos(1, 0, 0, 0, 0, player, pos);

	if (BattleManager::GetSingleton()->CharCollision())
	{
		moveSpeed = 0.0f;
	}
	else moveSpeed = 10.0f;

	if (action == eActs::moveBackward) moveSpeed = 10.0f;

	BattleManager::GetSingleton()->MapCollision(pos, kingSize.x * 2, moveSpeed, action);

	// 킹 맞았는지 체크
	if (BattleManager::GetSingleton()->Hit())
	{
		maxFrame = 3;
		ActionChange(eActs::hit, maxFrame);
		pos.x += player * (moveSpeed * 2);
	}

	// 킹 움직임, 공격 이미지 업데이트
	if (delay == false)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown(left))
		{
			switch (player)
			{
			case ePlayer::player1:
				if (action != eActs::moveBackward)
				{
					action = eActs::moveBackward;
					frameX = 9;
					elapsedCount = 0;
					maxFrame = 10;
				}
				break;
			case ePlayer::player2:
				if (action != eActs::moveForward)
				{
					action = eActs::moveForward;
					frameX = 0;
					elapsedCount = 0;
					maxFrame = 10;
				}				
				break;
			}

			elapsedCount += 2;
			if (elapsedCount >= frameRate)
			{
				frameX++;
				pos.x -= moveSpeed;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(right))
		{
			switch (player)
			{
			case ePlayer::player1:
				if (action != eActs::moveForward)
				{
					action = eActs::moveForward;
					frameX = 0;
					elapsedCount = 0;
					maxFrame = 10;
				}
				break;
			case ePlayer::player2:
				if (action != eActs::moveBackward)
				{
					action = eActs::moveBackward;
					frameX = 9;
					elapsedCount = 0;
					maxFrame = 10;
				}
				break;
			}

			elapsedCount += 2;
			if (elapsedCount >= frameRate)
			{
				frameX--;
				pos.x += moveSpeed;
				if (frameX <= 0)
				{
					frameX = 9;
				}
				elapsedCount = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(wP))
		{
			ActionChange(eActs::weekPunch, 7);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(sP))
		{
			ActionChange(eActs::strongPunch, 11);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(wK))
		{
			ActionChange(eActs::weekFoot, 8);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(sK))
		{
			ActionChange(eActs::strongFoot, 15);
		}
		else
		{
			action = eActs::standing;
			maxFrame = 8;
			elapsedCount++;
			if (elapsedCount >= frameRate)
			{
				frameX++;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
		}

		switch (player)
		{
		case player1:
			if (BattleManager::GetSingleton()->Getplayer1Lose())
			{
				ActionChange(eActs::die, 11);
			}
			else if (BattleManager::GetSingleton()->Getplayer1Win())
			{
				ActionChange(eActs::victory, 6);
			}
			break;
		case player2:
			if (BattleManager::GetSingleton()->Getplayer2Lose())
			{
				ActionChange(eActs::die, 11);
			}
			else if (BattleManager::GetSingleton()->Getplayer2Win())
			{
				ActionChange(eActs::victory, 6);
			}
			break;
		}
	}
	else
	{
		elapsedCount++;
		if (elapsedCount >= frameRate / 2 + 1)
		{
			frameX++;
			if (frameX >= maxFrame)
			{
				if (action == eActs::die || action == eActs::victory)
				{
					frameX = maxFrame;
				}
				else
				{
					action = eActs::standing;
					delay = false;
					frameX = 0;
					BattleManager::GetSingleton()->SetIsHit(false);
				}
				
			}
			elapsedCount = 0;
		}
	}

	HitBoxPos();
}

void King::Render(HDC hdc)
{
	if (img)
	{
		img[action].KingRender(hdc, pos.x, pos.y, frameX, frameY, player);
	}
}

void King::Release()
{
	if (img)
	{
		delete [] img;
		img = nullptr;
	}
}

void King::HitBoxPos()
{
	switch (action)
	{
	case eActs::weekPunch:
		if (frameX > 2 && frameX < 6)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 130, 50, 0, 30, player, punchPos);
			BattleManager::GetSingleton()->SetDamage(8);
		}
		break;
	case eActs::strongPunch:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 160, 50, 0, 30, player, punchPos);
			BattleManager::GetSingleton()->SetDamage(10);
		}
		break;
	case eActs::weekFoot:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 140, 20, 0, 110, player, kickPos);
			BattleManager::GetSingleton()->SetDamage(9);
		}
		break;
	case eActs::strongFoot:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 160, 125, 0, 0, player, kickPos);
			BattleManager::GetSingleton()->SetDamage(12);
		}
		break;
	}
}
