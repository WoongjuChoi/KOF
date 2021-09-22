#pragma once
#include "GameObject.h"
//#include "Image.h"	// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;	// ���԰���
class Hwajai : public GameObject	// ��Ӱ���
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

