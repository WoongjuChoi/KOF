#pragma once

#include "Config.h"
#include "GameObject.h"

class Image;
class King : public GameObject
{
private:
	Image* img;
	
	POINTFLOAT kingSize;

	POINTFLOAT punchPos;
	POINTFLOAT kickPos;
	
public:
	void Init(ePlayer p);
	void Update();
	void Render(HDC hdc);
	void Release();

	void HitBoxPos();
};