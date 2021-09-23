#pragma once
#include "GameObject.h"
#include "Config.h"
//#include "Image.h"	// 컴파일 관계가 복잡, 컴파일 시간이 오래 걸림

class Image;	// 포함관계
class Hwajai : public GameObject	// 상속관계
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

