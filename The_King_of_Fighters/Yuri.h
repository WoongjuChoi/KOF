#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Yuri : public GameObject
{
private:
	Image* yuri;
	Body* body;
	int hitLeft, hitTop, hitRight, hitBottom;
	POINTFLOAT hitPos;

public:
	void Init(ePlayer player);
	void Update();
	void Render(HDC hdc);
	void Release();

	bool IsCollision(Body body);
	void HitBoxPos();
};