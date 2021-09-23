#include "GameObject.h"

void GameObject::Move()
{
	//singleton1.ProcessInputKey();
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

void GameObject::SetBodyPos(Body& body, int posX, int posY, int leftPos, int rightPos, int topPos, int bottomPos)
{
	body.bodyPos.x = posX;
	body.bodyPos.y = posY;
	body.left = body.bodyPos.x - size / 2 + leftPos;
	body.right = body.bodyPos.x + size / 2 + rightPos;
	body.top = body.bodyPos.y - size / 2 + topPos;
	body.bottom = body.bodyPos.y + size / 2 + bottomPos;
}

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}
