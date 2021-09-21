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
	// ������ �����̱�
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

	// �ǽ�1. �ڷ� �����̱� + ���� ��ġ �̵�
	// ����. ���۾� �� �� ���ҽ� ã�ƺ���
	// (���ڸ� ���ֱ�, ������ �̵�, �ڷ� �̵�, ���� ��/��, ū ��/��
	// , �ǰ�(�¾��� ��)

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
