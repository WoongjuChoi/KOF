#include "GameEntity.h"
#include "Singleton.h"

void GameEntity::Init()
{
	//cout << "Hello World!!" << endl;
}

void GameEntity::Update()
{
	(*Singleton<int>::GetSingleton()) = 20;
}

void GameEntity::Render(HDC hdc)
{
}

void GameEntity::Release()
{
}
