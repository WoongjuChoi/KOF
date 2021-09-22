#pragma once
#include "GameObject.h"
//#include "Image.h"	// 컴파일 관계가 복잡, 컴파일 시간이 오래 걸림

class Image;	// 포함관계
class Hwajai : public GameObject	// 상속관계
{
private:
	typedef enum eActs { standing, move, weekPunch, weekFoot, strongPunch, strongFoot, hit, die, end };
	typedef enum eBody { top, bottom, hitPoint , bodyend };
	eActs action;
	Image* hwaj;
	int imageX;
	int frameX, frameY;
	int elapsedCount;
	bool delay;
	int maxFrame;
	int frameRate;

	int size;
	struct Body
	{
		int left, top, right, bottom;
		POINTFLOAT bodyPos;
	};
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

	void DrowBodyPos(HDC hdc, Body body);

	void SetBodyPos(Body &body, int leftPos, int rightPos, int topPos, int bottomPos);
};

