#include "SceneManager.h"
#pragma once
class Image;
class CharacterSelect : public SceneManager
{
public:

	Image* CSScene = nullptr;
	enum eChSel { cardFlip, selectCard, screenBorder, chSelect, midBorder, memBorder, cursor1, cursor2, readyP1, readyP2, chCard, chCircle, chHwajai, chKing, chYuri , hwajaiSelect, kingSelect, yuriSelect, sceneEnd };
	enum eCS {p1, p2, pEnd};

	int p1ChFrameX, p2ChFrameX, frameX, frameY;
	int elapsedCount, p1ChElapsedCount, p2ChElapsedCount;
	int maxFrame, p1ChMaxFrame, p2ChMaxFrame;
	int frameRate, p1ChFrameRate, p2ChFrameRate;
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

