#pragma once
#include "Config.h"

// �츮�� ������ ���� ����
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
	// Ÿ�̸�
	HANDLE hTimer;

	// UI
	char text[128];

	int mousePosX;
	int mousePosY;
	int clickedMousePosX;
	int clickedMousePosY;

	// �����
	Image* backBuffer;

	// ��� �̹���
	Image* backGround;

	// �÷��̾� ��ü
	eCharacter CharacterP1;
	eCharacter CharacterP2;

	GameObject* player1;
	GameObject* player2;

	// ĳ����
	Hwajai* hwajai;
	Yuri* yuri;
	King* king;

	//Ÿ��Ʋ
	TitleScene* titleScene;
	CharacterSelect* chSelect;
	BattleScene* battleScene;
	Winner* winnerScene;

public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
