#pragma once

#include "GameEntity.h"

class GameObject : public GameEntity
{
	//private:	// 외부 클래스에 노출시키지 않는다.
protected:	// 상속된 클래스에 노출시킨다.
//public:		// 모든 외부 클래스에 노출시킨다.
	POINTFLOAT pos;
	RECT shape;
	float moveSpeed;
	int bodySize;

public:
	void Move();

	// this가 nullptr이다. 코드상으로 함수를 객체가 호출했지만 객체가 없다. 에러
	inline void SetPos(POINTFLOAT pos) { this->pos = pos; }
	inline POINTFLOAT GetPos() { return this->pos; }
	inline void SetMoveSpeed(float speed) { this->moveSpeed = speed; }
	inline int GetBodySize() { return this->bodySize; }

	GameObject();
	~GameObject();
};

