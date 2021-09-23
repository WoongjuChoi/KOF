#include "King.h"
#include "Image.h"
#include "KeyManager.h"

void King::Init()
{
	// 킹 이미지 초기화
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
	maxFrame = 10;
	elapsedCount = 0;
	moveType = eMoveType::STANDING;
	moveSpeed = 10;
	bUpdateMove = false;

	characterPos.x = (WIN_SIZE_X / 2) ;
	characterPos.y = (WIN_SIZE_Y / 2) ;

	// 킹 캐릭터 상단, 하단 상자 만들기 & 히트상자 초기화
	body = new Body[eeBody::BODY_END];
	ConstructBody(body);
}

void King::Update()
{
	// 킹 맞았는지 체크
	if (isCollision(body[eeBody::BOTTOM]))
	{
		frameX = 0;
		maxFrame = 3;
		elapsedCount = 0;
		moveType = eMoveType::ATTACKED;
		bUpdateMove = true;
		characterPos.x += 20;
	}

	// 킹 움직임, 공격 이미지 업데이트
	if (bUpdateMove == false)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
		{
			maxFrame = 10;
			elapsedCount++;
			if (elapsedCount >= FRAME_RATE)
			{
				frameX++;
				characterPos.x -= moveSpeed;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
			moveType = eMoveType::MOVE_BACKWARD;
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
		{
			maxFrame = 10;
			elapsedCount++;
			if (elapsedCount >= FRAME_RATE)
			{
				frameX++;
				characterPos.x += moveSpeed;
				if (frameX >= maxFrame)
				{
					frameX = 0;
				}
				elapsedCount = 0;
			}
			moveType = eMoveType::MOVE_FOWARD;
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

	// 킹 캐릭터 상단, 하단 상자 업데이트
	UpdateBody(body);

	// 킹 히트포인트 업데이트
	CreateHitPoint(body);
}

void King::Render(HDC hdc)
{
	RenderBody(hdc, body);

	if (img)
	{
		img[moveType].KingRender(hdc, characterPos.x, characterPos.y, frameX, frameY);
	}

	Rectangle(hdc, 400, 270, 450, 320);
}

void King::Release()
{
	delete[] body;
	body = nullptr;

	if (img)
	{
		delete [] img;
		img = nullptr;
	}
}

void King::ConstructBody(Body*& body)
{
	body[eeBody::BOTTOM].size.x = 100;
	body[eeBody::BOTTOM].size.y = 100;

	body[eeBody::BOTTOM].pos.x = characterPos.x;
	body[eeBody::BOTTOM].pos.y = characterPos.y - (body[eeBody::BOTTOM].size.y / 2);

	body[eeBody::BOTTOM].shape.left = body[eeBody::BOTTOM].pos.x - (body[eeBody::BOTTOM].size.x / 2);
	body[eeBody::BOTTOM].shape.top = body[eeBody::BOTTOM].pos.y - (body[eeBody::BOTTOM].size.y / 2);
	body[eeBody::BOTTOM].shape.right = body[eeBody::BOTTOM].shape.left + body[eeBody::BOTTOM].size.x;
	body[eeBody::BOTTOM].shape.bottom = body[eeBody::BOTTOM].shape.top + body[eeBody::BOTTOM].size.y;

	body[eeBody::TOP].size.x = 80;
	body[eeBody::TOP].size.y = 100;

	body[eeBody::TOP].pos.x = body[eeBody::BOTTOM].pos.x + 10;
	body[eeBody::TOP].pos.y = body[eeBody::BOTTOM].pos.y -
		(body[eeBody::BOTTOM].size.y / 2) - (body[eeBody::TOP].size.y / 2);

	body[eeBody::TOP].shape.left = body[eeBody::TOP].pos.x - body[eeBody::TOP].size.x / 2;
	body[eeBody::TOP].shape.top = body[eeBody::TOP].pos.y - body[eeBody::TOP].size.y / 2;
	body[eeBody::TOP].shape.right = body[eeBody::TOP].shape.left + body[eeBody::TOP].size.x;
	body[eeBody::TOP].shape.bottom = body[eeBody::TOP].shape.top + body[eeBody::TOP].size.y;

	body[eeBody::HIT_POINT].size.x = 0;
	body[eeBody::HIT_POINT].size.y = 0;
	body[eeBody::HIT_POINT].pos.x = 0;
	body[eeBody::HIT_POINT].pos.y = 0;
	body[eeBody::HIT_POINT].shape.left = 0;
	body[eeBody::HIT_POINT].shape.right = 0;
	body[eeBody::HIT_POINT].shape.top = 0;
	body[eeBody::HIT_POINT].shape.bottom = 0;
}

void King::UpdateBody(Body*& body)
{
	body[eeBody::BOTTOM].pos.x = characterPos.x;
	body[eeBody::BOTTOM].pos.y = characterPos.y - (body[eeBody::BOTTOM].size.y / 2);

	body[eeBody::BOTTOM].shape.left = body[eeBody::BOTTOM].pos.x - (body[eeBody::BOTTOM].size.x / 2);
	body[eeBody::BOTTOM].shape.top = body[eeBody::BOTTOM].pos.y - (body[eeBody::BOTTOM].size.y / 2);
	body[eeBody::BOTTOM].shape.right = body[eeBody::BOTTOM].shape.left + body[eeBody::BOTTOM].size.x;
	body[eeBody::BOTTOM].shape.bottom = body[eeBody::BOTTOM].shape.top + body[eeBody::BOTTOM].size.y;

	body[eeBody::TOP].pos.x = body[eeBody::BOTTOM].pos.x + 10;
	body[eeBody::TOP].pos.y = body[eeBody::BOTTOM].pos.y -
		(body[eeBody::BOTTOM].size.y / 2) - (body[eeBody::TOP].size.y / 2);

	body[eeBody::TOP].shape.left = body[eeBody::TOP].pos.x - body[eeBody::TOP].size.x / 2;
	body[eeBody::TOP].shape.top = body[eeBody::TOP].pos.y - body[eeBody::TOP].size.y / 2;
	body[eeBody::TOP].shape.right = body[eeBody::TOP].shape.left + body[eeBody::TOP].size.x;
	body[eeBody::TOP].shape.bottom = body[eeBody::TOP].shape.top + body[eeBody::TOP].size.y;

	body[eeBody::HIT_POINT].size.x = 0;
	body[eeBody::HIT_POINT].size.y = 0;
	body[eeBody::HIT_POINT].pos.x = 0;
	body[eeBody::HIT_POINT].pos.y = 0;
	body[eeBody::HIT_POINT].shape.left = 0;
	body[eeBody::HIT_POINT].shape.right = 0;
	body[eeBody::HIT_POINT].shape.top = 0;
	body[eeBody::HIT_POINT].shape.bottom = 0;
}

void King::RenderBody(HDC hdc, Body*& body)
{
	Rectangle(hdc, body[eeBody::BOTTOM].shape.left, body[eeBody::BOTTOM].shape.top,
		body[eeBody::BOTTOM].shape.right, body[eeBody::BOTTOM].shape.bottom);
	Rectangle(hdc, body[eeBody::TOP].shape.left, body[eeBody::TOP].shape.top,
		body[eeBody::TOP].shape.right, body[eeBody::TOP].shape.bottom);
	Rectangle(hdc, body[eeBody::HIT_POINT].shape.left, body[eeBody::HIT_POINT].shape.top,
		body[eeBody::HIT_POINT].shape.right, body[eeBody::HIT_POINT].shape.bottom);
}

void King::CreateHitPoint(Body*& body)
{
	switch (moveType)
	{
	case eMoveType::WEAK_PUNCH:
		if (frameX >= 2 && frameX <= 4)
		{
			body[eeBody::HIT_POINT].size.x = 150;
			body[eeBody::HIT_POINT].size.y = 50;
			body[eeBody::HIT_POINT].pos.x = body[eeBody::TOP].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].pos.y = body[eeBody::TOP].pos.y - body[eeBody::HIT_POINT].size.y / 2;
			body[eeBody::HIT_POINT].shape.left = body[eeBody::HIT_POINT].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].shape.top = body[eeBody::HIT_POINT].pos.y - body[eeBody::HIT_POINT].size.y / 2;
			body[eeBody::HIT_POINT].shape.right = body[eeBody::HIT_POINT].shape.left + body[eeBody::HIT_POINT].size.x;
			body[eeBody::HIT_POINT].shape.bottom = body[eeBody::HIT_POINT].shape.top + body[eeBody::HIT_POINT].size.y;
		}
		break;
	case eMoveType::WEAK_KICK:
		if (frameX >= 2 && frameX <= 5)
		{
			body[eeBody::HIT_POINT].size.x = 150;
			body[eeBody::HIT_POINT].size.y = 140;
			body[eeBody::HIT_POINT].pos.x = body[eeBody::TOP].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].pos.y = body[eeBody::TOP].pos.y + body[eeBody::HIT_POINT].size.y / 2;
			body[eeBody::HIT_POINT].shape.left = body[eeBody::HIT_POINT].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].shape.top = body[eeBody::HIT_POINT].pos.y - body[eeBody::HIT_POINT].size.y / 2;
			body[eeBody::HIT_POINT].shape.right = body[eeBody::HIT_POINT].shape.left + body[eeBody::HIT_POINT].size.x;
			body[eeBody::HIT_POINT].shape.bottom = body[eeBody::HIT_POINT].shape.top + body[eeBody::HIT_POINT].size.y;
		}
		break;
	case eMoveType::STRONG_PUNCH:
		if (frameX >= 3 && frameX <= 6)
		{
			body[eeBody::HIT_POINT].size.x = 180;
			body[eeBody::HIT_POINT].size.y = 70;
			body[eeBody::HIT_POINT].pos.x = body[eeBody::TOP].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].pos.y = body[eeBody::TOP].pos.y - body[eeBody::HIT_POINT].size.y / 4;
			body[eeBody::HIT_POINT].shape.left = body[eeBody::HIT_POINT].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].shape.top = body[eeBody::HIT_POINT].pos.y - body[eeBody::HIT_POINT].size.y / 2;
			body[eeBody::HIT_POINT].shape.right = body[eeBody::HIT_POINT].shape.left + body[eeBody::HIT_POINT].size.x;
			body[eeBody::HIT_POINT].shape.bottom = body[eeBody::HIT_POINT].shape.top + body[eeBody::HIT_POINT].size.y;
		}
		break;
	case eMoveType::STRONG_KICK:
		if (frameX >= 3 && frameX <= 6)
		{
			body[eeBody::HIT_POINT].size.x = 170;
			body[eeBody::HIT_POINT].size.y = 150;
			body[eeBody::HIT_POINT].pos.x = body[eeBody::TOP].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].pos.y = body[eeBody::TOP].pos.y/* - body[eeBody::HIT_POINT].size.y / 2*/;
			body[eeBody::HIT_POINT].shape.left = body[eeBody::HIT_POINT].pos.x - body[eeBody::HIT_POINT].size.x / 2;
			body[eeBody::HIT_POINT].shape.top = body[eeBody::HIT_POINT].pos.y - body[eeBody::HIT_POINT].size.y / 2;
			body[eeBody::HIT_POINT].shape.right = body[eeBody::HIT_POINT].shape.left + body[eeBody::HIT_POINT].size.x;
			body[eeBody::HIT_POINT].shape.bottom = body[eeBody::HIT_POINT].shape.top + body[eeBody::HIT_POINT].size.y;
		}
		break;
	}
}

bool King::isCollision(Body bodyBottom)
{
	if (body[eeBody::BOTTOM].shape.left > 450)	  return false;
	if (body[eeBody::BOTTOM].shape.right < 400)  return false;
	if (body[eeBody::BOTTOM].shape.top > 320)	  return false;
	if (body[eeBody::BOTTOM].shape.bottom < 270) return false;

	return true;
}
