#include "SceneMng.h"
#include "DxLib.h"
#include "common/Vector2.h"
#include "Effect.h"
#include "NextMng.h"
#include <stdio.h>
#include <time.h>

SceneMng* SceneMng::s_instance = nullptr;

void SceneMng::Run(void)
{
	Init();
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		for (auto&& stage : playStage_)
		{
			stage->Update();
		}
		Draw();
		frame_++;
	}
}

SceneMng::SceneMng() : screenSize_({ 1280, 720 })
{
}

SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	DrawGraph(0, 0, backImage, true);
	/*DrawBox(0, 0, screenSize_.x, screenSize_.y, 0xffffff, true);*/
	for (auto&& stage : playStage_)
	{
		Vector2 pos = stage->GetOffset();
		DrawGraph(pos.x, pos.y,stage->GetStageDraw(),true);
	}
	lpEff.Draw();
	lpEff.Update();
	ScreenFlip();
}

bool SceneMng::Init(void)
{
	SetGraphMode(screenSize_.x, screenSize_.y, 16);
	ChangeWindowMode(true);
	SetWindowText("1916020_ìcíÜê^êl");
	SetDrawScreen(DX_SCREEN_BACK);						//  ﬁØ∏ ﬁØÃßÇ…ê›íË
	if (DxLib_Init() == -1)
	{
		return false;
	}
	frame_ = 0;
	backImage = LoadGraph("image/back.png", true);
	seed = (unsigned int)time(NULL);
	playStage_.emplace_back(std::make_unique<Stage>(std::move(Vector2(60, 80)), std::move(Vector2(288, 576))));
	/*playStage_.emplace_back(std::make_unique<Stage>(std::move(Vector2(60, 80)), std::move(Vector2(288, 576))));*/
	return true;
}
