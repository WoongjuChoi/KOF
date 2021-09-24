#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Yuri : public GameObject
{
private:
	Image* yuri;
	RECT hitBox[5]; // 0 : 몸통 1 : 약손 2 : 강손 3 : 약발 4 : 강발
	int hitLeft, hitTop, hitRight, hitBottom;
	POINTFLOAT hitPos;

public:
	void Init(ePlayer player);
	void Update();
	void Render(HDC hdc);
	void Release();

	void HitBoxPos();
};