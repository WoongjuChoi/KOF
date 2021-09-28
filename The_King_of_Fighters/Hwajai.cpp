#include "Hwajai.h"
#include "Image.h"
#include "BattleManager.h"
#include "KeyManager.h"

void Hwajai::Init(ePlayer P)
{
	GameObject::SetKey(P);
	player = P;

	imageX = 880;
	hwaj = new Image[eActs::end];
	maxFrame = 9;
	hwaj[eActs::standing].Init("Image/hwajai/standing.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 7;
	hwaj[eActs::moveForward].Init("Image/hwajai/walk.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 7;
	hwaj[eActs::moveBackward].Init("Image/hwajai/walk.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 12;
	hwaj[eActs::weekPunch].Init("Image/hwajai/weekpunch.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	hwaj[eActs::weekFoot].Init("Image/hwajai/weekfoot.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 8;
	hwaj[eActs::strongPunch].Init("Image/hwajai/strongpunch.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 12;
	hwaj[eActs::strongFoot].Init("Image/hwajai/strongfoot.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 4;
	hwaj[eActs::hit].Init("Image/hwajai/hit.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 9;
	hwaj[eActs::die].Init("Image/hwajai/die.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 6;
	hwaj[eActs::victory].Init("Image/hwajai/win.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));

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

	pos.y = WIN_SIZE_Y / 4 * 3 - 10;
	moveSpeed = 10.0f;

	size = imageX/8;
}

void Hwajai::Update()
{
	BattleManager::GetSingleton()->SetHitBoxPos(0, size / 2, size + 60, size / 2, size - 40, player, pos);
	BattleManager::GetSingleton()->SetHitBoxPos(1, 0, 0, 0, 0, player, pos);

	if (BattleManager::GetSingleton()->CharCollision())
	{
		moveSpeed = 0.0f;
	}
	else moveSpeed = 10.0f;

	if (action == eActs::moveBackward) moveSpeed = 10.0f;

	BattleManager::GetSingleton()->MapCollision(pos, size, moveSpeed, action);

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
			switch (player)
			{
			case ePlayer::player1:
				if (action != eActs::moveBackward)
				{
					action = eActs::moveBackward;
					frameX = 0;
					elapsedCount = 0;
					maxFrame = 6;
				}
				break;
			case ePlayer::player2:
				if (action != eActs::moveForward)
				{
					action = eActs::moveForward;
					frameX = 0;
					elapsedCount = 0;
					maxFrame = 6;
				}
				break;
			}

			elapsedCount++;
			if (elapsedCount >= frameRate)
			{
				frameX++;
				pos.x -= moveSpeed;
				if (frameX >= 6)
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
					maxFrame = 6;
				}
				break;
			case ePlayer::player2:
				if (action != eActs::moveBackward)
				{
					action = eActs::moveBackward;
					frameX = 0;
					elapsedCount = 0;
					maxFrame = 6;
				}
				break;
			}

			elapsedCount++;
			if (elapsedCount >= frameRate)
			{
				frameX--;
				pos.x += moveSpeed;
				if (frameX <= -1)
				{
					frameX = 5;
				}
				elapsedCount = 0;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(wP))
		{
			ActionChange(eActs::weekPunch, 12);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(sP))
		{
			ActionChange(eActs::strongPunch, 8);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(wK))
		{
			ActionChange(eActs::weekFoot, 10);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown(sK))
		{
			ActionChange(eActs::strongFoot, 12);
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
				ActionChange(eActs::die, 8);
			}
			else if (BattleManager::GetSingleton()->Getplayer1Win())
			{
				ActionChange(eActs::victory, 5);
			}
			break;
		case player2:
			if (BattleManager::GetSingleton()->Getplayer2Lose())
			{
				ActionChange(eActs::die, 8);
			}
			else if (BattleManager::GetSingleton()->Getplayer2Win())
			{
				ActionChange(eActs::victory, 5);
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
					BattleManager::GetSingleton()->SetIsHit(false);
					frameX = 0;
				}
			}
			elapsedCount = 0;
		}
	}

	HitBoxPos();			//히트박스 위치 세팅 함수

}

void Hwajai::Render(HDC hdc)
{
		hwaj[action].Render(hdc, pos.x, pos.y, frameX, frameY, player);
}

void Hwajai::Release()
{
	if (hwaj)
	{
		delete hwaj;
		hwaj = nullptr;
	}
}

void Hwajai::HitBoxPos()
{
	switch (action)
	{
	case eActs::weekPunch:
		if (frameX > 4 && frameX < 8)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 145, size + 30, -40, -90, player, pos);
			BattleManager::GetSingleton()->SetDamage(8);
		}
		break;
	case eActs::strongPunch:
		if (frameX > 2 && frameX < 6)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 160, size + 30, 40, -80, player, pos);
			BattleManager::GetSingleton()->SetDamage(10);
		}
		break;
	case eActs::weekFoot:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 145, size + 20, -10, -20, player, pos);
			BattleManager::GetSingleton()->SetDamage(9);
		}
		break;
	case eActs::strongFoot:
		if (frameX > 3 && frameX < 7)
		{
			BattleManager::GetSingleton()->SetHitBoxPos(1, 155, size + 20, -10, -20, player, pos);
			BattleManager::GetSingleton()->SetDamage(12);
		}
		break;
	}
}
