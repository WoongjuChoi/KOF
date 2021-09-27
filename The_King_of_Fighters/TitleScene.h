#include "GameObject.h"
#include "SceneManager.h"
#pragma once
class Image;
class TitleScene : public SceneManager
{
public:
	Image* title = nullptr;
	enum eTitle { intro, titleScene1, pressEnter, titleMain, sceneEnd };

	int frameX, frameY;
	int elapsedCount;
	int maxFrame;
	int frameRate;
	bool sceneChange;
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	TitleScene();
	~TitleScene();
};

