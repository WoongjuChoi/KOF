#include "Winner.h"
#include "Image.h"

void Winner::Init(eCharacter winner)
{
	winnerImage = new Image[winnerEnd];
	winnerImage[you_win].Init("Image/AfterBattle/you_win.bmp", 12160, 480, 19, 1, true, RGB(0,0,0));
	winnerImage[background].Init("Image/AfterBattle/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	switch (winner)
	{
	case eCharacter::eHwajai:
		winnerImage[winnerPlayer].Init("Image/AfterBattle/hawjai_win.bmp", 684, WIN_SIZE_Y, true, RGB(255, 255, 255));
		break;

	case eCharacter::eKing:
		winnerImage[winnerPlayer].Init("Image/AfterBattle/king_win.bmp", 524, WIN_SIZE_Y, true, RGB(255, 255, 255));
		break;

	case eCharacter::eYuri:
		winnerImage[winnerPlayer].Init("Image/AfterBattle/yuri_win.bmp", 532, WIN_SIZE_Y, true, RGB(255, 255, 255));
		break;
	}

	frameX = frameY = 0;
	elapsedCount = 0;
	maxFrame = 18;
	frameRate = 5;
}

void Winner::Update()
{
	elapsedCount++;
	if (elapsedCount > frameRate)
	{
		frameX++;
		if (frameX >= maxFrame)
		{
			frameX = maxFrame;
			SceneManager::GetSingleton()->setReadyChangeScene(true);
		}
		elapsedCount = 0;
	}
}

void Winner::Render(HDC hdc)
{
	winnerImage[background].Render(hdc);
	winnerImage[winnerPlayer].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
	winnerImage[you_win].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY, ePlayer::player2);
}



void Winner::Release()
{
	delete[] winnerImage;
	winnerImage = nullptr;
}
