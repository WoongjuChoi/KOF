#include "Yuri.h"
#include "Image.h"
#include "BattleManager.h"
#include "KeyManager.h"

void Yuri::Init(ePlayer P)
{
	GameObject::SetKey(P);
	player = P;

	imageX = 740;
	yuri = new Image[eActs::end];
	maxFrame = 9;
	yuri[eActs::standing].Init("Image/Yuri/Standing.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	yuri[eActs::moveForward].Init("Image/Yuri/MoveForward.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	yuri[eActs::moveBackward].Init("Image/Yuri/MoveBackwards.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 7;
	yuri[eActs::weekPunch].Init("Image/Yuri/LP.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 8;
	yuri[eActs::weekFoot].Init("Image/Yuri/LK.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 8;
	yuri[eActs::strongPunch].Init("Image/Yuri/HP.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	yuri[eActs::strongFoot].Init("Image/Yuri/HK.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 3;
	yuri[eActs::hit].Init("Image/Yuri/hit.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 13;
	yuri[eActs::die].Init("Image/Yuri/Lose.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 9;
	yuri[eActs::victory].Init("Image/Yuri/Victory.bmp", (imageX * maxFrame), 770, maxFrame, 1, true, RGB(255, 0, 255));

	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 9;
	frameRate = 5;
	action = eActs::standing;
	delay = false;

	if (player == ePlayer::player1)
	{
		pos.x = WIN_SIZE_X / 4;
	}
	else
	{
		pos.x = WIN_SIZE_X / 4 * 3;
	}
	
	pos.y = WIN_SIZE_Y / 4 * 3 - 90;
	moveSpeed = 10.0f;

	size = imageX / 7;
}

void Yuri::Update()
{
	BattleManager::GetSingleton()->SetHitBoxPos(0, size/2, size/2 + 10, size/2, size + 40, player, pos);
	BattleManager::GetSingleton()->SetHitBoxPos(1, 0, 0, 0, 0, player, pos);

	if (BattleManager::GetSingleton()->Hit())
	{
		maxFrame = 4;
		ActionChange(eActs::hit, maxFrame);
		pos.x += player * (moveSpeed * 2);
	}

	if (!delay)
	{
		elapsedCount++;
		if (elapsedCount > frameRate)
		{
			frameX++;
			if (frameX >= 9)
			{
				frameX = 0;
			}
			elapsedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(left))
		{
			if (action != eActs::moveForward)
			{
				action = eActs::moveForward;
				frameX = 0;
				elapsedCount = 0;
				maxFrame = 6;
			}
			elapsedCount++;
			if (elapsedCount >= frameRate)
			{
				frameX++;
				pos.x -= moveSpeed;
				if (frameX >= 8)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(right))
		{
			if (action != eActs::moveBackward)
			{
				action = eActs::moveBackward;
				frameX = 0;
				elapsedCount = 0;
				maxFrame = 5;
			}
			elapsedCount++;
			if (elapsedCount >= frameRate)
			{
				frameX++;
				pos.x += moveSpeed;
				if (frameX >= 10)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(wP))
		{
			ActionChange(eActs::weekPunch, 6);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(sP))
		{
			ActionChange(eActs::strongPunch, 7);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(wK))
		{
			ActionChange(eActs::weekFoot, 7);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(sK))
		{
			ActionChange(eActs::strongFoot, 10);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('U'))
		{
			ActionChange(eActs::die, 12);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			ActionChange(eActs::victory, 8);
		}
		else
		{
			action = eActs::standing;
		}

		switch (player)
		{
		case player1:
			if (BattleManager::GetSingleton()->Getplayer1Lose())
			{
				ActionChange(eActs::die, 12);
			}
			else if (BattleManager::GetSingleton()->Getplayer1Win())
			{
				ActionChange(eActs::victory, 8);
			}
			break;
		case player2:
			if (BattleManager::GetSingleton()->Getplayer2Lose())
			{
				ActionChange(eActs::die, 12);
			}
			else if (BattleManager::GetSingleton()->Getplayer2Win())
			{
				ActionChange(eActs::victory, 8);
			}
			break;
		}
	}
	else
	{
		elapsedCount++;
		if (elapsedCount >= frameRate)
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
					BattleManager::GetSingleton()->SetIsHit(false);
					frameX = 0;
				}
			}
			elapsedCount = 0;
		}
	}

	HitBoxPos();			//히트박스 위치 세팅 함수
}

void Yuri::Render(HDC hdc)
{
	yuri[action].Render(hdc, pos.x, pos.y, frameX, frameY, player);
}

void Yuri::Release()
{
	if (yuri)
	{
		delete yuri;
		yuri = nullptr;
	}
}

void Yuri::HitBoxPos()
{
	switch (action)
	{
	case eActs::weekPunch:
		if (frameX > 3 && frameX < 6)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 80, size / 2, 40, 20, player, pos);
			BattleManager::GetSingleton()->SetDamage(8);
		}
		break;
	case eActs::strongPunch:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 130, size / 2, 0, 20, player, pos);
			BattleManager::GetSingleton()->SetDamage(10);
		}
		break;
	case eActs::weekFoot:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 130, size / 2 + 10, 0, size, player, pos);
			BattleManager::GetSingleton()->SetDamage(9);
		}
		break;
	case eActs::strongFoot:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 155, size / 2, 0, 20, player, pos);
			BattleManager::GetSingleton()->SetDamage(12);
		}
		break;
	}
}
