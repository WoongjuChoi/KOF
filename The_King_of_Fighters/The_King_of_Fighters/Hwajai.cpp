#include "Hwajai.h"
#include "Image.h"
#include "KeyManager.h"

void Hwajai::Init()
{
	imageX = 880;
	hwaj = new Image[eActs::end];
	maxFrame = 9;
	hwaj[eActs::standing].Init("Image/hwajai/standing.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 7;
	hwaj[eActs::move].Init("Image/hwajai/walk.bmp", (imageX * maxFrame), 611, maxFrame, 1, true, RGB(255, 0, 255));
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

	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 9;
	frameRate = 5;
	action = eActs::standing;
	delay = false;
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 10.0f;
}

void Hwajai::Update()
{
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

		else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			if (action != eActs::move)
			{
				action = eActs::move;
				frameX = 0;
				elapsedCount = 0;
				maxFrame = 6;
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
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			if (action != eActs::move)
			{
				action = eActs::move;
				frameX = 0;
				elapsedCount = 0;
				maxFrame = 5;
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
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
		{
			action = eActs::weekPunch;
			delay = true;
			maxFrame = 12;
			frameX = 0;
			elapsedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('T'))
		{
			action = eActs::strongPunch;
			delay = true;
			maxFrame = 8;
			frameX = 0;
			elapsedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{
			action = eActs::weekFoot;
			delay = true;
			maxFrame = 10;
			frameX = 0;
			elapsedCount = 0;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
		{
			action = eActs::strongFoot;
			delay = true;
			maxFrame = 12;
			frameX = 0;
			elapsedCount = 0;
		}
		else
		{
			action = eActs::standing;
		}

	}
	else
	{
		elapsedCount++;
		if (elapsedCount >= frameRate/2)
		{
			frameX++;
			if (frameX >= maxFrame)
			{
				action = eActs::standing;
				delay = false;
				frameX = 0;
			}
			elapsedCount = 0;
		}
	}


	//else
	//{
	//	action = eActs::standing;
	//}

}

void Hwajai::Render(HDC hdc)
{
	
		hwaj[action].Render(hdc, pos.x, pos.y, frameX, frameY);
}

void Hwajai::Release()
{
	if (hwaj)
	{
		delete hwaj;
		hwaj = nullptr;
	}
}
