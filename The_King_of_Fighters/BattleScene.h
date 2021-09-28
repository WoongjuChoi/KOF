#pragma once
#include "GameObject.h"
#include "SceneManager.h"


class Image;
class BattleScene
{
private:
	enum eBattle {
		P1Character, P2Character, HP_bar, HP_gage_p1, HP_gage_p2,
		guard_gage, time_infinite, stage, KO, round1, ready, ready_bar, GO, eBattleEnd
	};

	Image* battleImage = nullptr;

	float hpCalculate;
	int HPdamageP1;
	int HPdamageP2;

	int frameX, frameY;
	int elapsedCount;
	int maxFrame;
	int frameRate;
	int delay, delayCount;
	bool sceneChange;
	bool reset;
	eBattle nowImage;

public:
	void Init(eCharacter CharacterP1, eCharacter CharacterP2);
	void Update();
	void Render(HDC hdc);
	void Release();
};

