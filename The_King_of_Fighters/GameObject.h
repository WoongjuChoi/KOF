#pragma once

// ������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����
// �ʱ�ȭ (�޸� �Ҵ�), 1ȸ�� ����
// ������Ʈ, ���������� �����Ӹ��� ����
// ���, ���������� �����Ӹ��� ����
// �޸� ����, 1ȸ�� ����

/*
	��� : �ߺ��Ǵ� �ڵ带 ���� �� �ִ�.
	�߻�ȭ : ���Ǽ��迡 �ִ� ��ü�� ���Ӱ�ü�� �ʿ��� �����͸� �߷��� ��.

	Ŭ���� �߻�ȭ : Ŭ���� �� ����Ǵ� ������� �߷��� ��.
*/

#include "GameEntity.h"
#include "Config.h"

struct Body
{
	int left, top, right, bottom;
	POINTFLOAT bodyPos;
};

class GameObject : public GameEntity
{
	//private:	// �ܺ� Ŭ������ �����Ű�� �ʴ´�.
protected:	// ��ӵ� Ŭ������ �����Ų��.
//public:		// ��� �ܺ� Ŭ������ �����Ų��.
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

public:
	void Move();

	// this�� nullptr�̴�. �ڵ������ �Լ��� ��ü�� ȣ�������� ��ü�� ����. ����
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

	void ActionChange(eActs act, int frame);
	void DrowBodyPos(HDC hdc, Body body);
	void SetBodyPos(Body& body, int posX, int posY, int leftPos, int rightPos, int topPos, int bottomPos);

	GameObject();
	~GameObject();
};


