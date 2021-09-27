#include "TitleScene.h"
#include "Image.h"


void TitleScene::Init()
{
	title = new Image[sceneEnd];
	title[intro].Init("Image/Title/intro_logo.bmp", 2560, 480, 4, 1, true, RGB(0, 0, 0));
	title[titleMain].Init("Image/Title/pressenter.bmp", 1366, 768, 1, 1, true, RGB(255, 0, 255));
	title[pressEnter].Init("Image/Title/press_enter1.bmp", 12800, 480, 20, 1, true, RGB(0, 0, 0));

	SceneManager::GetSingleton()->Init();
	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 9;
	frameRate = 5;
	sceneChange = true;
}

void TitleScene::Update()
{
	elapsedCount++;
	if (elapsedCount > frameRate)
	{
		frameX++;
		if (frameX >= maxFrame)
		{
			frameX = 0;
		}
		elapsedCount = 0;
	}

}

void TitleScene::Render(HDC hdc)
{

	if (sceneChange)
	{
		maxFrame = 5;		//4프레임으로 할 시 씬 변경이 되지않음
		frameRate = 60;
		title[intro].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, 0,1);
		if (frameX+1 == maxFrame)
		{
			sceneChange = false;
		}
	}
	else
	{
		SceneManager::GetSingleton() ->setReadyChangeScene(true);
		maxFrame = 10;
		frameRate = 5;
		title[titleMain].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0,1);
		title[pressEnter].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2 + 100, frameX, 0, 1);
	}


	
}

void TitleScene::Release()
{
	if (title)
	{
		delete title;
		title = nullptr;
	}
}

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}
