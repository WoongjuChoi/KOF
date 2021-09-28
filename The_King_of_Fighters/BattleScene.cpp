#include "BattleScene.h"
#include "Image.h"
#include "BattleManager.h"

void BattleScene::Init(eCharacter CharacterP1, eCharacter CharacterP2)
{

	battleImage = new Image[eBattle::eBattleEnd];
	battleImage[HP_bar].Init("Image/Battle/HP_bar.bmp", /*1300, 150*/676, 79, true, RGB(255, 0, 255));
	battleImage[HP_gage_p1].Init("Image/Battle/HP_gage.bmp", 214, 9, true, RGB(255, 0, 255));
	battleImage[HP_gage_p2].Init("Image/Battle/HP_gage_2.bmp", 214, 9, true, RGB(255, 0, 255));
	battleImage[guard_gage].Init("Image/Battle/guard_gage.bmp", 97, 4, true, RGB(0, 0, 0));
	battleImage[time_infinite].Init("Image/Battle/time_infinite.bmp", 640, 480, true, RGB(255, 0, 255));
	battleImage[stage].Init("Image/Battle/Japan_Stage.bmp", 2559, 466);
	battleImage[KO].Init("Image/Battle/KO_1.bmp", 9600, 480, 15, 1, true, RGB(255, 0, 255));

	battleImage[round1].Init("Image/Battle/BattleIntro/round1.bmp", 4480, 480, 7, 1, true, RGB(255, 0, 255));
	battleImage[ready].Init("Image/Battle/BattleIntro/ready.bmp", 6400, 480, 10, 1, true, RGB(255, 0, 255));
	battleImage[ready_bar].Init("Image/Battle/BattleIntro/ready_inside.bmp", 5760, 480, 9, 1, true, RGB(255, 0, 255));
	battleImage[GO].Init("Image/Battle/BattleIntro/GO.bmp", 9600, 480, 15, 1, true, RGB(0, 0, 0));

	switch (CharacterP1)
	{
	case eCharacter::eHwajai:
		battleImage[P1Character].Init("Image/Battle/hwajai.bmp", 85, 82, true, RGB(255, 0, 255));
		break;
	case eCharacter::eKing:
		battleImage[P1Character].Init("Image/Battle/king.bmp", 85, 82, true, RGB(255, 0, 255));
		break;
	case eCharacter::eYuri:
		battleImage[P1Character].Init("Image/Battle/yuri.bmp", 85, 82, true, RGB(255, 0, 255));
		break;
	}

	switch (CharacterP2)
	{
	case eCharacter::eHwajai:
		battleImage[P2Character].Init("Image/Battle/hwajai_reverse.bmp", 85, 82, true, RGB(255, 0, 255));
		break;
	case eCharacter::eKing:
		battleImage[P2Character].Init("Image/Battle/king_reverse.bmp", 85, 82, true, RGB(255, 0, 255));
		break;
	case eCharacter::eYuri:
		battleImage[P2Character].Init("Image/Battle/yuri_reverse.bmp", 85, 82, true, RGB(255, 0, 255));
		break;
	}

	hpCalculate = 214 / 100.0f;

	frameX = 0;
	frameY = 0;
	elapsedCount = 0;
	maxFrame = 14;
	frameRate = 1;
	sceneChange = false;
	reset = false;
	nowImage = eBattle::round1;
}

void BattleScene::Update()
{
	HPdamageP1 = 100 - BattleManager::GetSingleton()->Getplayer1Hp();
	HPdamageP2 = 100 - BattleManager::GetSingleton()->Getplayer2Hp();

	if (nowImage == eBattle::round1 || nowImage == eBattle::ready_bar || nowImage == eBattle::ready || nowImage == eBattle::GO)
	{
		elapsedCount++;
		if (elapsedCount > frameRate)
		{
			frameX++;
			//if (frameX >= maxFrame)
			//{
			//	frameX =0;


			//}
			elapsedCount = 0;
		}
	}

	if (BattleManager::GetSingleton()->Getplayer1Win() || BattleManager::GetSingleton()->Getplayer2Win())
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
}

void BattleScene::Render(HDC hdc)
{
	if (sceneChange)
	{
		/*battleImage[stage].BattleRender(hdc, 0, 0);*/
		battleImage[HP_bar].BattleRender(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 10);
		battleImage[HP_gage_p1].HpRender(hdc, WIN_SIZE_X / 2 - 134, WIN_SIZE_Y / 10 - 12,
			hpCalculate, HPdamageP1, ePlayer::player1);
		battleImage[HP_gage_p2].HpRender(hdc, WIN_SIZE_X / 2 + 134, WIN_SIZE_Y / 10 - 12,
			hpCalculate, HPdamageP2, ePlayer::player2);
		battleImage[time_infinite].BattleRender(hdc, WIN_SIZE_X / 2 + 9, 186);
		battleImage[guard_gage].BattleRender(hdc, WIN_SIZE_X / 2 - 76, WIN_SIZE_Y / 10 - 1);
		battleImage[guard_gage].BattleRender(hdc, WIN_SIZE_X / 2 + 75, WIN_SIZE_Y / 10 - 1);
		battleImage[P1Character].BattleRender(hdc, WIN_SIZE_X / 2 - 280, WIN_SIZE_Y / 10 - 14);
		battleImage[P2Character].BattleRender(hdc, WIN_SIZE_X / 2 + 280, WIN_SIZE_Y / 10 - 14);

		if (BattleManager::GetSingleton()->Getplayer1Win() || BattleManager::GetSingleton()->Getplayer2Win())
		{
			battleImage[KO].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY, ePlayer::player2);
		}
	}
	else
	{
		if (nowImage == eBattle::round1)
		{
			if (reset == false)
			{
				delay = 0;
				delayCount = 30;
				maxFrame = 7;
				reset = true;
			}
			battleImage[round1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY, 1);
			if (frameX >= maxFrame)
			{
				delay++;
				battleImage[round1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 6, frameY, 1);
				if (delay >= delayCount)
				{
					elapsedCount = frameRate;
					reset = false;
					nowImage = eBattle::ready_bar;
				}
			}
		}
		else if (nowImage == eBattle::ready_bar)
		{
			if (reset == false)
			{
				delay = 0;
				delayCount = 50;
				frameX = 0;
				maxFrame = 9;
				reset = true;
			}
			battleImage[ready_bar].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY, 1);
			battleImage[round1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 6, frameY, 1);

			if (frameX >= maxFrame)
			{
				delay++;
				battleImage[ready_bar].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 8, frameY, 1);
				battleImage[round1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 6, frameY, 1);
				if (delay >= delayCount)
				{
					elapsedCount = frameRate;
					reset = false;
					nowImage = eBattle::ready;
				}
			}
		}
		else if (nowImage == eBattle::ready)
		{
			if (reset == false)
			{
				delay = 0;
				delayCount = 70;
				frameX = 0;
				maxFrame = 9;
				reset = true;
			}
			battleImage[ready].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY, 1);
			battleImage[round1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 6, frameY, 1);
			if (frameX >= maxFrame)
			{
				delay++;
				battleImage[ready].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 9, frameY, 1);
				battleImage[round1].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 6, frameY, 1);
				if (delay >= delayCount)
				{
					elapsedCount = frameRate;
					reset = false;
					nowImage = eBattle::GO;
				}
			}
		}
		else if (nowImage == eBattle::GO)
		{
			if (reset == false)
			{
				delay = 0;
				delayCount = 30;
				frameX = 0;
				maxFrame = 15;
				reset = true;
			}
			battleImage[GO].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, frameX, frameY, 1);
			if (frameX >= maxFrame)
			{
				delay++;
				battleImage[GO].Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2, 14, frameY, 1);
				if (delay >= delayCount)
				{
					frameX = 0;
					maxFrame = 15;
					frameRate = 4;
					reset = false;
					sceneChange = true;
					nowImage = eBattle::eBattleEnd;
				}
			}

		}
	}
}

void BattleScene::Release()
{
	delete[] battleImage;
	battleImage = nullptr;
}
