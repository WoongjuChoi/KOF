#pragma once
#include "Config.h"

// 우리가 구성할 게임 월드
class Image;
class Yuri;
class Hwajai;
class King;
class GameObject;
class TitleScene;
class CharacterSelect;
class BattleScene;
class Winner;
class MainGame
{
private:
	// 타이머
	HANDLE hTimer;

	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	// 백버퍼
	Image* backBuffer;

	// 배경 이미지
	Image* backGround;

	// 플레이어 객체
	eCharacter CharacterP1;
	eCharacter CharacterP2;

	GameObject* player1;
	GameObject* player2;

	// 캐릭터
	Hwajai* hwajai;
	Yuri* yuri;
	King* king;

	//타이틀
	TitleScene* titleScene;
	CharacterSelect* chSelect;
	BattleScene* battleScene;
	Winner* winnerScene;

public:
	void Init();
	void Update();
	//void Render();			// 오버라이딩 : 상속 관계에서 부모클래스의 함수를 재정의
	void Render(HDC hdc);	// 오버로딩
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
