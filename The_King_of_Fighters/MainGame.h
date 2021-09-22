#pragma once
#include "Config.h"
#include "GameEntity.h"

// �츮�� ������ ���� ����
class Image;
class Iori;
class Hwajai;
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

	// �̿���
	Iori* iori;

	Hwajai* hwajai;

public:
	void Init();
	void Update();
	//void Render();			// �������̵� : ��� ���迡�� �θ�Ŭ������ �Լ��� ������
	void Render(HDC hdc);	// �����ε�
	void Release();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};