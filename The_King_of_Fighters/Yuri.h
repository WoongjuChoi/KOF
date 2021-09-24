#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Yuri : public GameObject
{
private:
	Image* yuri;
	RECT hitBox[5]; // 0 : ���� 1 : ��� 2 : ���� 3 : ��� 4 : ����
	int hitLeft, hitTop, hitRight, hitBottom;
	POINTFLOAT hitPos;

public:
	void Init(ePlayer player);
	void Update();
	void Render(HDC hdc);
	void Release();

	void HitBoxPos();
};