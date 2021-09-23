#include "Yuri.h"
#include "Image.h"
#include "KeyManager.h"

void Yuri::Init()
{
	imageX = 740;
	yuri = new Image[eActs::end];
	body = new Body[eBody::bodyend];
	maxFrame = 9;
	yuri[eActs::standing].Init("Image/Yuri/Standing.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	yuri[eActs::moveForward].Init("Image/Yuri/MoveForward.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	yuri[eActs::moveBackward].Init("Image/Yuri/MoveBackwards.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 7;
	yuri[eActs::weekPunch].Init("Image/Yuri/LP.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 8;
	yuri[eActs::weekFoot].Init("Image/Yuri/LK.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 8;
	yuri[eActs::strongPunch].Init("Image/Yuri/HP.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 10;
	yuri[eActs::strongFoot].Init("Image/Yuri/HK.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 3;
	yuri[eActs::hit].Init("Image/Yuri/hit.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 13;
	yuri[eActs::die].Init("Image/Yuri/Lose.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));
	maxFrame = 9;
	yuri[eActs::victory].Init("Image/Yuri/Victory.bmp", (imageX * maxFrame), 700, maxFrame, 1, true, RGB(255, 0, 255));

	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 9;
	frameRate = 5;
	action = eActs::standing;
	delay = false;
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;
	moveSpeed = 10.0f;

	size = imageX / 8;
}

void Yuri::Update()
{
	SetBodyPos(body[eBody::bottom], pos.x, pos.y, 0, 0, 0, 0);
	SetBodyPos(body[eBody::top], pos.x, pos.y - size, 30, -10, 0, 0);
	SetBodyPos(body[eBody::hitPoint], 0, 0, 0, 0, 0, 0);

	if (IsCollision(body[eBody::bottom]))
	{
		maxFrame = 4;
		ActionChange(eActs::hit, maxFrame);
		pos.x += moveSpeed * 2;
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

		else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
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
		else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
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
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
		{
			ActionChange(eActs::weekPunch, 6);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('T'))
		{
			ActionChange(eActs::strongPunch, 7);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{
			ActionChange(eActs::weekFoot, 7);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
		{
			ActionChange(eActs::strongFoot, 10);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('Y'))
		{
			ActionChange(eActs::hit, 3);
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

	}
	else
	{
		elapsedCount++;
		if (elapsedCount >= frameRate)
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

	HitBoxPos();			//히트박스 위치 세팅 함수
}

void Yuri::Render(HDC hdc)
{
	yuri[action].Render(hdc, pos.x, pos.y, frameX, frameY);

	DrowBodyPos(hdc, body[eBody::bottom]);			//하체부분
	DrowBodyPos(hdc, body[eBody::top]);				//상체부분
	DrowBodyPos(hdc, body[eBody::hitPoint]);			//히트박스



	MoveToEx(hdc, 300, 300, NULL);					//임시로만든 박스
	LineTo(hdc, 300, 350);
	LineTo(hdc, 350, 350);
	LineTo(hdc, 350, 300);
	LineTo(hdc, 300, 300);

}

void Yuri::Release()
{
	if (yuri)
	{
		delete yuri;
		yuri = nullptr;
	}
}

bool Yuri::IsCollision(Body body)
{
	//숫자부분은 상대 히트박수 수치
	if (body.left > 350)	return false;
	if (body.right < 300)	return false;
	if (body.top > 350)	return false;
	if (body.bottom < 300)	return false;


	return true;
}

void Yuri::HitBoxPos()
{
	switch (action)
	{
	case eActs::weekPunch:
		if (frameX > 4 && frameX < 8)
		{
			body[eBody::hitPoint].bodyPos.x = pos.x - size;
			body[eBody::hitPoint].bodyPos.y = pos.y - size;
			body[eBody::hitPoint].left = body[eBody::hitPoint].bodyPos.x - size / 2 + 22;
			body[eBody::hitPoint].right = body[eBody::hitPoint].bodyPos.x + size / 2 - 8;
			body[eBody::hitPoint].top = body[eBody::hitPoint].bodyPos.y - size / 2 + 38;
			body[eBody::hitPoint].bottom = body[eBody::hitPoint].bodyPos.y + size / 2 - 47;
		}
		break;
	case eActs::strongPunch:
		if (frameX > 2 && frameX < 6)
		{
			body[eBody::hitPoint].bodyPos.x = pos.x - size;
			body[eBody::hitPoint].bodyPos.y = pos.y - size;
			body[eBody::hitPoint].left = body[eBody::hitPoint].bodyPos.x - size / 2 + 5;
			body[eBody::hitPoint].right = body[eBody::hitPoint].bodyPos.x + size / 2 - 8;
			body[eBody::hitPoint].top = body[eBody::hitPoint].bodyPos.y - size / 2 + 42;
			body[eBody::hitPoint].bottom = body[eBody::hitPoint].bodyPos.y + size / 2 - 38;
		}
		break;
	case eActs::weekFoot:
		if (frameX > 3 && frameX < 7)
		{
			body[eBody::hitPoint].bodyPos.x = pos.x - size;
			body[eBody::hitPoint].bodyPos.y = pos.y - size;
			body[eBody::hitPoint].left = body[eBody::hitPoint].bodyPos.x - size / 2 + 7;
			body[eBody::hitPoint].right = body[eBody::hitPoint].bodyPos.x + size / 2 - 8;
			body[eBody::hitPoint].top = body[eBody::hitPoint].bodyPos.y - size / 2 + 55;
			body[eBody::hitPoint].bottom = body[eBody::hitPoint].bodyPos.y + size / 2 - 13;
		}
		break;
	case eActs::strongFoot:
		if (frameX > 3 && frameX < 7)
		{
			body[eBody::hitPoint].bodyPos.x = pos.x - size;
			body[eBody::hitPoint].bodyPos.y = pos.y - size;
			body[eBody::hitPoint].left = body[eBody::hitPoint].bodyPos.x - size / 2 + 7;
			body[eBody::hitPoint].right = body[eBody::hitPoint].bodyPos.x + size / 2 - 8;
			body[eBody::hitPoint].top = body[eBody::hitPoint].bodyPos.y - size / 2 + 45;
			body[eBody::hitPoint].bottom = body[eBody::hitPoint].bodyPos.y + size / 2 - 17;
		}
		break;
	}
}
