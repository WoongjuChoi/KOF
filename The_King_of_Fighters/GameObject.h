#pragma once
#include "GameEntity.h"
#include "Config.h"
#include <windef.h>

struct Body
{
	RECT hitBox;
	POINTFLOAT bodyPos;
};

class Yuri;
class King;
class Hwajai;
class GameObject : public GameEntity
{
protected:
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySize;
	int imageX;
	int frameX, frameY;
	int elapsedCount;
	int maxFrame;
	int frameRate;
	int size;
	bool delay;
	eActs action;
	ePlayer player;
	GameObject* target;

	char left, right, wP, sP, wK, sK;
	ePlayer chosenPlayer;
	eCharacter chosenCharacter;

	King* king;
	Yuri* yuri;
	Hwajai* hwajai;

public:
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

	void ActionChange(eActs act, int frame);
	void DrowBodyPos(HDC hdc, Body body);
	void SetBodyPos(Body& body, int posX, int posY, int leftPos, int rightPos, int topPos, int bottomPos, ePlayer player);
	void SetKey(ePlayer player);

	inline void SetChosenPlayer(ePlayer chosenPlayer) { this->chosenPlayer = chosenPlayer; }
	inline void SetChosenCharacter(eCharacter chosenCharacter) { this->chosenCharacter = chosenCharacter; }

	GameObject();
	~GameObject();
};


