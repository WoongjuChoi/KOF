#pragma once
#include "Config.h"
#include "GameObject.h"
//#include "Image.h"	// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;	// ���԰���
class Hwajai : public GameObject	// ��Ӱ���
{
private:
	Image* hwaj;
	int hitLeft, hitTop, hitRight, hitBottom;
	POINTFLOAT hitPos;
public:
	void Init(ePlayer player);
	void Update();
	void Render(HDC hdc);
	void Release();

	void HitBoxPos();
};

