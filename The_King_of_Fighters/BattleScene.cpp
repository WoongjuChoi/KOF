#include "BattleScene.h"
#include "Image.h"
//#include "BattleManager.h"

void BattleScene::Init()
{

	battleImage = new Image[eBattle::eBattleEnd];
	battleImage[hwajai].Init("Image/Battle/hwajai.bmp", 85, 82, true, RGB(255, 0, 255));
	battleImage[king].Init("Image/Battle/king.bmp", 85, 82, true, RGB(255, 0, 255));
	battleImage[yuri].Init("Image/Battle/yuri_reverse.bmp", 85, 82, true, RGB(255, 0, 255));
	battleImage[HP_bar].Init("Image/Battle/HP_bar.bmp", /*1300, 150*/676, 79, true, RGB(255, 0, 255));
	battleImage[HP_gage_p1].Init("Image/Battle/HP_gage.bmp", 214, 9, true, RGB(255, 0, 255));
	battleImage[HP_gage_p2].Init("Image/Battle/HP_gage_2.bmp", 214, 9, true, RGB(255, 0, 255));
	battleImage[guard_gage].Init("Image/Battle/guard_gage.bmp", 97, 4, true, RGB(0, 0, 0));
	battleImage[time_infinite].Init("Image/Battle/time_infinite.bmp", 640, 480, true, RGB(255, 0, 255));
	battleImage[stage].Init("Image/Battle/Japan_Stage.bmp", 2559, 466);

	hpCalculate = 214 / 100;

}

void BattleScene::Update()
{
	/*HPdamageP1 = 100 - BattleManager::GetSingleton()->Getplayer1Hp();
	HPdamageP2 = 100 - BattleManager::GetSingleton()->Getplayer2Hp();*/
}

void BattleScene::Render(HDC hdc)
{
	if (battleImage)
	{
		/*battleImage[stage].BattleRender(hdc, 0, 0);*/
		battleImage[HP_bar].BattleRender(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y /10);
		battleImage[HP_gage_p1].BattleRender(hdc, WIN_SIZE_X / 2 - 134, WIN_SIZE_Y / 10 - 12);
		battleImage[HP_gage_p2].BattleRender(hdc, WIN_SIZE_X / 2 + 134, WIN_SIZE_Y / 10 - 12);
		battleImage[time_infinite].BattleRender(hdc, WIN_SIZE_X / 2 + 9, 186);
		battleImage[guard_gage].BattleRender(hdc, WIN_SIZE_X / 2 - 76, WIN_SIZE_Y / 10 - 1);
		battleImage[guard_gage].BattleRender(hdc, WIN_SIZE_X / 2 + 75, WIN_SIZE_Y / 10 - 1);
		battleImage[hwajai].BattleRender(hdc, WIN_SIZE_X / 2 - 280, WIN_SIZE_Y / 10 - 14);
		battleImage[yuri].BattleRender(hdc, WIN_SIZE_X / 2 + 280, WIN_SIZE_Y / 10 - 14);
	}
	

	/*battleImage[HP_gage_p1].HpRenderRender(hdc, 20, 20, hpCalculate, HPdamageP1);
	battleImage[HP_gage_p2].HpRenderRender(hdc, WIN_SIZE_X - 234, 20, hpCalculate, HPdamageP2);*/
}

void BattleScene::Release()
{
	delete[] battleImage;
	battleImage = nullptr;
}
