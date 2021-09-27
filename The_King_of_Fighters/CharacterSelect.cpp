#include "CharacterSelect.h"
#include "Image.h"
#include "KeyManager.h"

void CharacterSelect::Init()
{
	CSScene = new Image[sceneEnd];
	CSScene[cardFlip].Init("Image/CharacterSelect/flip_card_part.bmp", 22400, 480, 35, 1, true, RGB(255, 0, 255));
	CSScene[selectCard].Init("Image/CharacterSelect/select_card_part.bmp", 640, 480, 1, 1, true, RGB(255, 0, 255));
	CSScene[screenBorder].Init("Image/CharacterSelect/screen_border.bmp", 640, 480, 1, 1, true, RGB(255, 0, 255));
	CSScene[midBorder].Init("Image/CharacterSelect/menu_middle.bmp", 640, 480, 1, 1, true, RGB(255, 0, 255));
	CSScene[memBorder].Init("Image/CharacterSelect/member.bmp", 640, 480, 1, 1, true, RGB(255, 0, 255));
	CSScene[cursor1].Init("Image/CharacterSelect/cursor_1P.bmp", 2250, 115, 30, 1, true, RGB(0, 0, 0));
	CSScene[cursor2].Init("Image/CharacterSelect/cursor_2P.bmp", 2250, 115, 30, 1, true, RGB(0, 0, 0));
	CSScene[readyP1].Init("Image/CharacterSelect/readyp1.bmp", 640, 480, 1, 1, true, RGB(255, 0, 255));
	CSScene[readyP2].Init("Image/CharacterSelect/readyp2.bmp", 640, 480, 1, 1, true, RGB(255, 0, 255));

	SceneManager::GetSingleton()->Init();
	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 35;
	frameRate = 2;
	sceneChange = true;

	ready[p1] = false;
	ready[p2] = false;

	select[p1] = 0;
	select[p2] = 2;
	CS[0].x = 350;
	CS[0].y = 617;
	CS[1].x = 450;
	CS[1].y = 617;
	CS[2].x = 550;
	CS[2].y = 617;


}

void CharacterSelect::Update()
{
	elapsedCount++;
	if (elapsedCount > frameRate)
	{
		frameX++;
		if (frameX >= maxFrame)
		{
			frameX = 0;
		}
		elapsedCount = 0;
	}

	if (ready[p1] == false)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('D'))
		{
			if (select[p1] >= 2)
			{
				select[p1] = 0;
			}
			else
			{
				select[p1]++;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('A'))
		{
			if (select[p1] <= 0)
			{
				select[p1] = 2;
			}
			else
			{
				select[p1]--;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('R'))
		{
			ready[p1] = true;
		}
	}


	if (ready[p2] == false)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('J'))
		{
			if (select[p2] >= 2)
			{
				select[p2] = 0;
			}
			else
			{
				select[p2]++;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('H'))
		{
			if (select[p2] <= 0)
			{
				select[p2] = 2;
			}
			else
			{
				select[p2]--;
			}
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
		{
			ready[p2] = true;
		}
	}

	if (ready[p1] && ready[p2])
	{
		SceneManager::GetSingleton()->setReadyChangeScene(true);
	}

}

void CharacterSelect::Render(HDC hdc)
{
	if (sceneChange)
	{
		CSScene[cardFlip].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, 0, 1);
		if (frameX + 1 == maxFrame)
		{
			maxFrame = 30;
			sceneChange = false;
		}
	}
	else
	{
		
		CSScene[selectCard].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0, 1);
		CSScene[cursor1].Render(hdc, CS[select[p1]].x, CS[select[p1]].y, frameX, 0, ePlayer::player2);
		CSScene[cursor2].Render(hdc, CS[select[p2]].x, CS[select[p2]].y, frameX, 0, ePlayer::player2);

	}
	CSScene[screenBorder].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0, 1);
	CSScene[midBorder].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0, 1);
	CSScene[memBorder].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0, 1);


	if (ready[p1])
	{
		CSScene[readyP1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0, 1);
	}

	if (ready[p2])
	{
		CSScene[readyP2].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 0, 0, 1);
	}

}

void CharacterSelect::Release()
{
}

eCharacter CharacterSelect::SelectP1Card()
{
	if (select[p1] == 0) return eCharacter::eHwajai;
	if (select[p1] == 1) return eCharacter::eKing;
	if (select[p1] == 2) return eCharacter::eYuri;
}
eCharacter CharacterSelect::SelectP2Card()
{
	if (select[p2] == 0) return eCharacter::eHwajai;
	if (select[p2] == 1) return eCharacter::eKing;
	if (select[p2] == 2) return eCharacter::eYuri;
}
