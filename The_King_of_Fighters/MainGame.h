#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
class Image;
class Yuri;
class Hwajai;
class GameObject;
class MainGame : public GameEntity
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

public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};
