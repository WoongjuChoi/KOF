#include "MainGame.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Hwajai.h"
#include "Yuri.h"
#include "TitleScene.h"
#include "CharacterSelect.h"

//int MainGame::clickedMousePosX = 0;

void MainGame::Init()
{
	//Singleton<int> singleton1;
	//singleton1.ProcessInputKey();
	//Singleton<KeyManager>::GetSingleton()->Init();

	//KeyManager keyMgr;
	KeyManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();	//�� �Ŵ��� �̴� Title


	// Ÿ�̸� ����
	hTimer = (HANDLE)SetTimer(g_hWnd, 0, 10, NULL);

	// �����
	backBuffer = new Image;
	backBuffer->Init(WIN_SIZE_X, WIN_SIZE_Y);

	// ��� �̹���
	backGround = new Image;
	if (!SUCCEEDED(backGround->Init("Image/Stage.bmp", 1400, 933)))
	{
		cout << "Image/bin.bmp ���� �ε忡 �����ߴ�." << endl;
	}

	player1 = new GameObject;
	player2 = new GameObject;

	//CharacterP1 = eCharacter::eYuri;
	CharacterP1 = eCharacter::eHwajai;
	//CharacterP2 = eCharacter::eHwajai;
	CharacterP2 = eCharacter::eYuri;

	player1->SetChosenPlayer(ePlayer::player1);
	player1->SetChosenCharacter(CharacterP1);

	player2->SetChosenPlayer(ePlayer::player2);
	player2->SetChosenCharacter(CharacterP2);


	player1->Init();
	player2->Init();

	titleScene = new TitleScene;
	titleScene->Init();

	chSelect = new CharacterSelect;
	chSelect->Init();
	// ĳ����
	/*player1->Init(ePlayer::player2, eCharacter::eHwajai);
	player2->Init(ePlayer::player1, eCharacter::eYuri);*/

	/*yuri = new Yuri;
	yuri->Init(ePlayer::player1);

	hwajai = new Hwajai;
	hwajai->Init(ePlayer::player2);*/

}

void MainGame::Update()
{
	
	//player1->Update();
	//player2->Update();

	if (SceneManager::GetSingleton()->getScene() == eScene::title)
	{
		titleScene->Update();
	}
	else if (SceneManager::GetSingleton()->getScene() == eScene::cSelect)
	{
		chSelect->Update();
	}
	else if (SceneManager::GetSingleton()->getScene() == eScene::battle)
	{
		player1->Update();
		player2->Update();
	}
	//chSelect->Update();
	InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render(HDC hdc)
{
	HDC hBackBufferDC = backBuffer->GetMemDC();

	//backGround->Render(hBackBufferDC);


	//player1->Render(hBackBufferDC);
	//player2->Render(hBackBufferDC);

	if (SceneManager::GetSingleton()->getScene() == eScene::title)				//title �� ���
	{
		titleScene->Render(hBackBufferDC);
		if (SceneManager::GetSingleton()->getReadyChangeScene() == true)		//�غ���� üũ
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))			//space Ű�Է�
			{
				SceneManager::GetSingleton()->setScene(eScene::cSelect);		//�� ����
				SceneManager::GetSingleton()->setReadyChangeScene(false);
			}
		}
	}
	else if (SceneManager::GetSingleton()->getScene() == eScene::cSelect)		//ĳ���� ���þ�
	{
		chSelect->Render(hBackBufferDC);
		if (SceneManager::GetSingleton()->getReadyChangeScene() == true)
		{

		}
	}
	else if (SceneManager::GetSingleton()->getScene() == eScene::battle)
	{
		backGround->Render(hBackBufferDC);
		player1->Render(hBackBufferDC);
		player2->Render(hBackBufferDC);
	}
	//chSelect->Render(hBackBufferDC);
	backBuffer->Render(hdc);
	
	
}

void MainGame::Release()
{
	SAFE_RELEASE(backBuffer);

	SAFE_RELEASE(backGround);

	/*player1->Release(eCharacter::eYuri);
	player2->Release(eCharacter::eHwajai);*/

	SAFE_RELEASE(hwajai);
	SAFE_RELEASE(yuri);
	
	// Ÿ�̸� ��ü ����
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
