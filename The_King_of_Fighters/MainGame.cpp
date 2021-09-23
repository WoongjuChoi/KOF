#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Hwajai.h"
#include "Yuri.h"

//int MainGame::clickedMousePosX = 0;

void MainGame::Init()
{
	//Singleton<int> singleton1;
	//singleton1.ProcessInputKey();
	//Singleton<KeyManager>::GetSingleton()->Init();

	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton();


	// 타이머 셋팅
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// 백버퍼
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// 배경 이미지
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/Stage.bmp", 1400, 933)))
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;
	}

	// 캐릭터
	player1->Init(ePlayer::player2, eCharacter::eHwajai);
	player2->Init(ePlayer::player1, eCharacter::eYuri);

	/*yuri = new Yuri;
	yuri->Init(ePlayer::player1);*/

}

void MainGame::Update()
{
	player1->Update(eCharacter::eYuri);
	player2->Update(eCharacter::eHwajai);
	/*if (hwajai)
	{
		hwajai->Update();
	}
	if (yuri)
	{
		yuri->Update();
	}*/

	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	backGround->Render(hBackBufferDC);

	player1->Render(hBackBufferDC, eCharacter::eYuri);
	player2->Render(hBackBufferDC, eCharacter::eHwajai);

	/*hwajai->Render(hBackBufferDC);

	yuri->Render(hBackBufferDC);*/

	backBuffer->Render(hdc);
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	SAFE_RELEASE(backGround);

	player1->Release(eCharacter::eYuri);
	player2->Release(eCharacter::eHwajai);

	/*SAFE_RELEASE(hwajai);
	SAFE_RELEASE(yuri);*/

	// 타이머 객체 삭제
	KillTimer(g_hWnd, 0);
}


LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		}
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
