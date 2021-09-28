#pragma once
#include "GameObject.h"
#include "SceneManager.h"


class Image;
class Winner : public SceneManager
{
private:
	enum eWinner {winnerPlayer, you_win, background, winnerEnd};

	Image* winnerImage = nullptr;

	int frameX, frameY;
	int elapsedCount;
	int maxFrame;
	int frameRate;

public:
	void Init(eCharacter winner);
	void Update();
	void Render(HDC hdc);
	void Release();
};

