#pragma once
#include "GameEntity.h"
#include "Config.h"
#include "Hwajai.h"
#include "Yuri.h"

struct Body
{
	int left, top, right, bottom;
	POINTFLOAT bodyPos;
};

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

	Hwajai* hwajai = nullptr;
	Yuri* yuri = nullptr;

	char left, right, wP, sP, wK, sK;

public:
	void Init(ePlayer player, eCharacter charecter);
	void Update(eCharacter charecter);
	void Render(HDC hdc, eCharacter charecter);
	void Release(eCharacter charecter);

	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

	void ActionChange(eActs act, int frame);
	void DrowBodyPos(HDC hdc, Body body);
	void SetBodyPos(Body& body, int posX, int posY, int leftPos, int rightPos, int topPos, int bottomPos, ePlayer player);
	void SetKey(ePlayer player);

	GameObject();
	~GameObject();
};


