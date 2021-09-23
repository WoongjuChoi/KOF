#include "Yuri.h"
#include "Image.h"
#include "KeyManager.h"

void Yuri::Init(ePlayer P)
{
	GameObject::SetKey(P);
	player = P;

	imageX = 740;
	yuri = new Image[eActs::end];
	body = new Body[eBody::bodyend];
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
	SetBodyPos(body[eBody::bottom], pos.x, pos.y + 90, 10, -10, 0, 0, ePlayer::player2);
	SetBodyPos(body[eBody::top], pos.x, pos.y - size + 90, 30, -10, 5, 0, ePlayer::player2);
	SetBodyPos(body[eBody::hitPoint], 0, 0, 0, 0, 0, 0, ePlayer::player2);

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
	yuri[action].Render(hdc, pos.x, pos.y, frameX, frameY, ePlayer::player1);

	DrowBodyPos(hdc, body[eBody::bottom]);			//하체부분
	DrowBodyPos(hdc, body[eBody::top]);				//상체부분
	DrowBodyPos(hdc, body[eBody::hitPoint]);			//히트박스



	MoveToEx(hdc, 300, 400, NULL);					//임시로만든 박스
	LineTo(hdc, 300, 450);
	LineTo(hdc, 350, 450);
	LineTo(hdc, 350, 400);
	LineTo(hdc, 300, 400);

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
	if (body.left > 450)	return false;
	if (body.right < 400)	return false;
	if (body.top > 450)	return false;
	if (body.bottom < 400)	return false;


	return true;
}

void Yuri::HitBoxPos()
{
	switch (action)
	{
	case eActs::weekPunch:
		if (frameX > 3 && frameX < 6)
		{
			SetBodyPos(body[eBody::hitPoint], pos.x -50, pos.y -10, 22, -8, 38, -47, ePlayer::player2);
		}
		break;
	case eActs::strongPunch:
		if (frameX > 3 && frameX < 7)
		{
			SetBodyPos(body[eBody::hitPoint], pos.x - 80, pos.y - 10, 5, 10, 35, -10, ePlayer::player2);
		}
		break;
	case eActs::weekFoot:
		if (frameX > 3 && frameX < 7)
		{
			SetBodyPos(body[eBody::hitPoint], pos.x - 70, pos.y - 70, 7, -8, 55, size / 2, ePlayer::player2);
		}
		break;
	case eActs::strongFoot:
		if (frameX > 3 && frameX < 7)
		{
			SetBodyPos(body[eBody::hitPoint], pos.x - 70, pos.y, -30, 0, 0, 0, ePlayer::player2);
		}
		break;
	}
}
