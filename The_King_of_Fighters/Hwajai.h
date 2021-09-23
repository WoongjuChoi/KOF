#pragma once
#include "GameObject.h"
#include "Config.h"
//#include "Image.h"	// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;	// ���԰���
class Hwajai : public GameObject	// ��Ӱ���
{
private:
	Image* hwaj;
	Body *body;
	int hitLeft, hitTop, hitRight, hitBottom;
	POINTFLOAT hitPos;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	bool IsCollision(Body body);
	void HitBoxPos();
};

