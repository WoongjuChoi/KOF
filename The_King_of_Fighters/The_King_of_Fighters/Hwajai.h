#pragma once
#include "GameObject.h"
//#include "Image.h"	// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;	// ���԰���
class Hwajai : public GameObject	// ��Ӱ���
{
private:
	typedef enum eActs { standing, move, weekPunch, weekFoot, strongPunch, strongFoot, hit, die, end };
	eActs action;
	Image* hwaj;
	int imageX;
	int frameX, frameY;
	int elapsedCount;
	bool delay;
	int maxFrame;
	int frameRate;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

