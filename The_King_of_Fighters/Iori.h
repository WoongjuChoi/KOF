#pragma once
#include "GameObject.h"
//#include "Image.h"	// ������ ���谡 ����, ������ �ð��� ���� �ɸ�

class Image;	// ���԰���
class Iori : public GameObject	// ��Ӱ���
{
private:
	Image* img;
	int frameX, frameY;
	int elapsedCount;
	int maxFrame;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

