#include "GameObject.h"
#include "Hwajai.h"
#include "Yuri.h"
#include "King.h"

void GameObject::Init()
{
	switch (chosenPlayer)
	{
	case player1:
		charPos.x = WIN_SIZE_X / 5;
		charPos.y = WIN_SIZE_Y * 3 / 4;

		switch (chosenCharacter)
		{
		case eHwajai:
			hwajai = new Hwajai;
			hwajai->Init(ePlayer::player1);
			break;

		case eYuri:
			yuri = new Yuri;
			yuri->Init(ePlayer::player1);
			break;

		case eKing:
			king = new King;
			king->Init(ePlayer::player1);
			break;
		}
		break;

	case player2:
		charPos.x = WIN_SIZE_X * 4 / 5;
		charPos.y = WIN_SIZE_Y * 3 / 4;

		switch (chosenCharacter)
		{
		case eHwajai:
			hwajai = new Hwajai;
			hwajai->Init(ePlayer::player2);
			break;

		case eYuri:
			yuri = new Yuri;
			yuri->Init(ePlayer::player2);
			break;

		case eKing:
			king = new King;
			king->Init(ePlayer::player2);
			break;
		}

		break;
	}
}

void GameObject::Update()
{
	switch (chosenPlayer)
	{
	case player1:
		switch (chosenCharacter)
		{
		case eHwajai:
			hwajai->Update();
			break;

		case eYuri:
			yuri->Update();
			break;

		case eKing:
			king->Update();
			break;
		}
		break;

	case player2:
		switch (chosenCharacter)
		{
		case eHwajai:
			hwajai->Update();
			break;

		case eYuri:
			yuri->Update();
			break;

		case eKing:
			king->Update();
			break;
		}

		break;
	}
}

void GameObject::Render(HDC hdc)
{
	switch (chosenPlayer)
	{
	case player1:
		switch (chosenCharacter)
		{
		case eHwajai:
			hwajai->Render(hdc);
			break;

		case eYuri:
			yuri->Render(hdc);
			break;

		case eKing:
			king->Render(hdc);
			break;
		}
		break;

	case player2:
		switch (chosenCharacter)
		{
		case eHwajai:
			hwajai->Render(hdc);
			break;

		case eYuri:
			yuri->Render(hdc);
			break;

		case eKing:
			king->Render(hdc);
			break;
		}

		break;
	}
}

void GameObject::Release()
{
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
	MoveToEx(hdc, body.hitBox.left, body.hitBox.top, NULL);
	LineTo(hdc, body.hitBox.left, body.hitBox.bottom);
	LineTo(hdc, body.hitBox.right, body.hitBox.bottom);
	LineTo(hdc, body.hitBox.right, body.hitBox.top);
	LineTo(hdc, body.hitBox.left, body.hitBox.top);
}

void GameObject::SetBodyPos(Body& body, int posX, int posY, int leftPos, int rightPos, int topPos, int bottomPos, ePlayer player)
{
	switch (player)
	{
	case ePlayer::player1:
		body.bodyPos.x = -posX;
		body.bodyPos.y = posY;
		body.hitBox.left = -(body.bodyPos.x - size / 2 + leftPos);
		body.hitBox.right = -(body.bodyPos.x + size / 2 + rightPos);
		body.hitBox.top = body.bodyPos.y - size / 2 + topPos;
		body.hitBox.bottom = body.bodyPos.y + size / 2 + bottomPos;
		break;
	case ePlayer::player2:
		body.bodyPos.x = posX;
		body.bodyPos.y = posY;
		body.hitBox.left = body.bodyPos.x - size / 2 + leftPos;
		body.hitBox.right = body.bodyPos.x + size / 2 + rightPos;
		body.hitBox.top = body.bodyPos.y - size / 2 + topPos;
		body.hitBox.bottom = body.bodyPos.y + size / 2 + bottomPos;
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
