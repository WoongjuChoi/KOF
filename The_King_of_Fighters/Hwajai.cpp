#include "Hwajai.h"
#include "Image.h"
#include "KeyManager.h"

void Hwajai::Init()
{
	imageX = 880;
	hwaj = new Image[eActs::end];
	body = new Body[eBody::bodyend];
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



	size = imageX/8;
}

void Hwajai::Update()
{
	SetBodyPos(body[eBody::bottom], pos.x, pos.y, 15, -10, 0, 0);
	SetBodyPos(body[eBody::top], pos.x, pos.y - size, 30, -10, 0, 0);
	SetBodyPos(body[eBody::hitPoint], 0, 0, 0, 0, 0, 0);

	if (IsCollision(body[eBody::bottom]))
	{
		maxFrame = 4;
		ActionChange(eActs::hit, maxFrame);
		pos.x += moveSpeed*2;
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
			ActionChange(eActs::weekPunch, 12);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('T'))
		{
			ActionChange(eActs::strongPunch, 8);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
		{
			ActionChange(eActs::weekFoot, 10);
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
		{
			ActionChange(eActs::strongFoot, 12);
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

void Hwajai::Render(HDC hdc)
{
		hwaj[action].Render(hdc, pos.x, pos.y, frameX, frameY);

		DrowBodyPos(hdc, body[eBody::bottom]);			//하체부분
		DrowBodyPos(hdc, body[eBody::top]);				//상체부분
		DrowBodyPos(hdc, body[eBody::hitPoint]);			//히트박스



		MoveToEx(hdc, 300, 300, NULL);					//임시로만든 박스
		LineTo(hdc, 300, 350);
		LineTo(hdc, 350, 350);
		LineTo(hdc, 350, 300);
		LineTo(hdc, 300, 300);
}

void Hwajai::Release()
{
	if (hwaj)
	{
		delete hwaj;
		hwaj = nullptr;
	}
}

bool Hwajai::IsCollision(Body body)
{
	//숫자부분은 상대 히트박수 수치
	if (body.left > 350)	return false;
	if (body.right < 300)	return false;
	if (body.top > 350)	return false;
	if (body.bottom < 300)	return false;


	return true;
}

void Hwajai::HitBoxPos()
{
	switch (action)
	{
	case eActs::weekPunch:
		if (frameX > 4 && frameX < 8)
		{
			body[eBody::hitPoint].bodyPos.x = pos.x - size;
			body[eBody::hitPoint].bodyPos.y = pos.y - size;
			body[eBody::hitPoint].left = body[eBody::hitPoint].bodyPos.x - size / 2			 + 22;
			body[eBody::hitPoint].right = body[eBody::hitPoint].bodyPos.x + size / 2			 - 8;
			body[eBody::hitPoint].top = body[eBody::hitPoint].bodyPos.y - size / 2			 + 38;
			body[eBody::hitPoint].bottom = body[eBody::hitPoint].bodyPos.y + size / 2			- 47;
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
