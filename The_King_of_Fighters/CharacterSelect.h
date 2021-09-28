#include "SceneManager.h"
#pragma once
class Image;
class CharacterSelect : public SceneManager
{
public:

	Image* CSScene = nullptr;
	enum eChSel { cardFlip, selectCard, screenBorder, chSelect, midBorder, memBorder, cursor1, cursor2, readyP1, readyP2, chCard, chCircle, chHwajai, chKing, chYuri , hwajaiSelect, kingSelect, yuriSelect, sceneEnd };
	enum eCS {p1, p2, pEnd};

	int chFrameX, frameX, frameY;
	int elapsedCount, chElapsedCount;
	int maxFrame, chMaxFrame;
	int frameRate, chFrameRate;
	bool sceneChange;

	int select[eCS::pEnd];
	bool ready[eCS::pEnd];
	POINT CS[3];

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	eCharacter SelectP1Card();
	eCharacter SelectP2Card();

	//CharacterSelect();
	//~CharacterSelect();
};

