#pragma once

#include "Config.h"
#include "GameObject.h"

#define FRAME_RATE 6

enum eMoveType
{
	STANDING, MOVE_FOWARD, MOVE_BACKWARD, WEAK_PUNCH, WEAK_KICK, 
	STRONG_PUNCH, STRONG_KICK, ATTACKED, END
};

enum eeBody { TOP, BOTTOM, HIT_POINT, BODY_END };

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
	
	POINTFLOAT characterPos;

	struct Body
	{
		POINT size;
		POINTFLOAT pos;
		RECT shape;
	};
	Body* body;

	
public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void ConstructBody(Body*& body);
	void UpdateBody(Body*& body);
	void RenderBody(HDC hdc, Body*& body);
	void CreateHitPoint(Body*& body);

	bool isCollision(Body bodyBottom);
};

