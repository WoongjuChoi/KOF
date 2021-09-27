#pragma once
#include "GameObject.h"
#include "SceneManager.h"


class Image;
class BattleScene
{
private:
	enum eBattle {
		hwajai, king, yuri, HP_bar, HP_gage_p1, HP_gage_p2,
		guard_gage, time_infinite, stage, eBattleEnd
	};

	Image* battleImage = nullptr;

	float hpCalculate;
	int HPdamageP1;
	int HPdamageP2;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};
