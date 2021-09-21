#include "King.h"
#include "Image.h"
#include "KeyManager.h"

void King::Init()
{
	img = new Image[eMoveType::END];
	img[eMoveType::STANDING].Init("King/King_Standing.bmp", 4650, 576, 10, 1, true, RGB(255, 0, 255));
	img[eMoveType::MOVE_FOWARD].Init("King/King_MoveFoward.bmp", 4650, 576, 10, 1, true, RGB(255, 0, 255));
	img[eMoveType::MOVE_BACKWARD].Init("King/King_MoveBackward.bmp", 4650, 576, 10, 1, true, RGB(255, 0, 255));
	img[eMoveType::WEAK_PUNCH].Init("King/King_WeakPunch.bmp", 3255, 576, 7, 1, true, RGB(255, 0, 255));
	img[eMoveType::WEAK_KICK].Init("King/King_WeakKick.bmp", 3720, 576, 8, 1, true, RGB(255, 0, 255));
	img[eMoveType::STRONG_PUNCH].Init("King/King_StrongPunch.bmp", 5115, 576, 11, 1, true, RGB(255, 0, 255));
	img[eMoveType::STRONG_KICK].Init("King/King_StrongKick.bmp", 6975, 576, 15, 1, true, RGB(255, 0, 255));
	img[eMoveType::ATTACKED].Init("King/King_Attacked.bmp", 1395, 576, 3, 1, true, RGB(255, 0, 255));

	frameX = 0;
	frameY = 0;
	elapsedCount = 0;

	pos.x = WIN_SIZE_X / 4;
	pos.y = WIN_SIZE_Y / 2;

	moveType = eMoveType::STANDING;
	maxFrame = 10;
	moveSpeed = 5;

	bUpdateMove = false;
}

void King::Update()
{
	if (bUpdateMove == false)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			maxFrame = 10;
			elapsedCount++;
			if (elapsedCount >= FRAME_RATE)
			{
				frameX++;
				pos.x += moveSpeed;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
			moveType = eMoveType::MOVE_FOWARD;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			maxFrame = 10;
			elapsedCount++;
			if (elapsedCount >= FRAME_RATE)
			{
				frameX++;
				pos.x -= moveSpeed;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
			moveType = eMoveType::MOVE_BACKWARD;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
		{
			maxFrame = 7;
			moveType = eMoveType::WEAK_PUNCH;
			frameX = 0;
			bUpdateMove = true;
			
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('T'))
		{
			maxFrame = 11;
			moveType = eMoveType::STRONG_PUNCH;
			frameX = 0;
			bUpdateMove = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{
			maxFrame = 8;
			moveType = eMoveType::WEAK_KICK;
			frameX = 0;
			bUpdateMove = true;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
		{
			maxFrame = 15;
			moveType = eMoveType::STRONG_KICK;
			frameX = 0;
			bUpdateMove = true;
			
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
		{
			maxFrame = 3;
			moveType = eMoveType::ATTACKED;
			frameX = 0;
			bUpdateMove = true;
		}
		else
		{
			maxFrame = 10;
			elapsedCount++;
			if (elapsedCount >= FRAME_RATE)
			{
				frameX++;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
			moveType = eMoveType::STANDING;
		}
	}
	else
	{
		elapsedCount++;
		if (elapsedCount >= FRAME_RATE)
		{
			frameX++;
			if (frameX >= maxFrame)
			{
				moveType = eMoveType::STANDING;
				bUpdateMove = false;
				frameX = 0;
			}
			elapsedCount = 0;
		}
	}
}

void King::Render(HDC hdc)
{
	if (img)
	{
		img[moveType].Render(hdc, pos.x, pos.y, frameX, frameY);
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
