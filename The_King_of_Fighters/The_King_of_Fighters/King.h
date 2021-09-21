#pragma once

#include "Config.h"
#include "GameObject.h"

#define FRAME_RATE 6	

enum eMoveType
{
	STANDING, MOVE_FOWARD, MOVE_BACKWARD, WEAK_PUNCH, WEAK_KICK, 
	STRONG_PUNCH, STRONG_KICK, ATTACKED, END
};

class Image;
class King : public GameObject
{
private:
	Image* img;
	int frameX;
	int frameY;
	int maxFrame;
	int elapsedCount;
	eMoveType moveType;
	bool bUpdateMove;
	
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

