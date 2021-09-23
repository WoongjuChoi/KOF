#include "GameObject.h"

void GameObject::Init(ePlayer player, eCharacter charecter)
{
	switch (charecter)
	{
	case eHwajai:
		hwajai = new Hwajai;
		hwajai->Init(player);
		break;
	case eYuri:
		yuri = new Yuri;
		yuri->Init(player);
		break;
	case eKing:
		break;
	}
}

void GameObject::Update(eCharacter charecter)
{
	switch (charecter)
	{
	case eHwajai:
		hwajai->Update();
		break;
	case eYuri:
		yuri->Update();
		break;
	case eKing:
		break;
	}
}

void GameObject::Render(HDC hdc, eCharacter charecter)
{
	switch (charecter)
	{
	case eHwajai:
		hwajai->Render(hdc);
		break;
	case eYuri:
		yuri->Render(hdc);
		break;
	case eKing:
		break;
	}
}

void GameObject::Release(eCharacter charecter)
{
	switch (charecter)
	{
	case eHwajai:
		hwajai->Release();
		break;
	case eYuri:
		yuri->Release();
		break;
	case eKing:
		break;
	}
}

void GameObject::ActionChange(eActs act, int frame)
{
	action = act;
	delay = true;
	maxFrame = frame;
	frameX = 0;
	elapsedCount = 0;
}

void GameObject::DrowBodyPos(HDC hdc, Body body)
{
	MoveToEx(hdc, body.left, body.top, NULL);
	LineTo(hdc, body.left, body.bottom);
	LineTo(hdc, body.right, body.bottom);
	LineTo(hdc, body.right, body.top);
	LineTo(hdc, body.left, body.top);
}

void GameObject::SetBodyPos(Body& body, int posX, int posY, int leftPos, int rightPos, int topPos, int bottomPos, ePlayer player)
{
	switch (player)
	{
	case ePlayer::player1:
		body.bodyPos.x = -posX;
		body.bodyPos.y = posY;
		body.left = -(body.bodyPos.x - size / 2 + leftPos);
		body.right = -(body.bodyPos.x + size / 2 + rightPos);
		body.top = body.bodyPos.y - size / 2 + topPos;
		body.bottom = body.bodyPos.y + size / 2 + bottomPos;
		break;
	case ePlayer::player2:
		body.bodyPos.x = posX;
		body.bodyPos.y = posY;
		body.left = body.bodyPos.x - size / 2 + leftPos;
		body.right = body.bodyPos.x + size / 2 + rightPos;
		body.top = body.bodyPos.y - size / 2 + topPos;
		body.bottom = body.bodyPos.y + size / 2 + bottomPos;
		break;
	}
}

void GameObject::SetKey(ePlayer player)
{
	switch (player)
	{
	case ePlayer::player1:
		left = 'A';
		right = 'D';
		wP = 'R';
		sP = 'T';
		wK = 'F';
		sK = 'G';
		break;
	case ePlayer::player2:
		left = 'H';
		right = 'J';
		wP = 'I';
		sP = 'O';
		wK = 'K';
		sK = 'L';
		break;
	}
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
