#include "Iori.h"
#include "Image.h"
#include "KeyManager.h"

void Iori::Init()
{
	img = new Image;
	img->Init("Image/Iori_walk.bmp", 612, 104, true, RGB(255, 0, 255));

	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 9;
}

void Iori::Update()
{
	// 앞으로 움직이기
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		elapsedCount++;
		if (elapsedCount >= 10)
		{
			frameX++;
			if (frameX >= maxFrame)
			{
				frameX = 0;
			}
			elapsedCount = 0;
		}
	}

	// 실습1. 뒤로 움직이기 + 실제 위치 이동
	// 과제. 팀작업 때 쓸 리소스 찾아보기
	// (제자리 서있기, 앞으로 이동, 뒤로 이동, 작은 손/발, 큰 손/발
	// , 피격(맞았을 때)

}

void Iori::Render(HDC hdc)
{
	if (img)
	{
		img->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY);
	}
}

void Iori::Release()
{
	if (img)
	{
		delete img;
		img = nullptr;
	}
}
