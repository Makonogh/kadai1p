#include "SceneMng.h"
#include "DxLib.h"
#include "common/Vector2.h"


SceneMng* SceneMng::s_instance = nullptr;

void SceneMng::Run(void)
{
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

SceneMng::SceneMng()
{
	Init();
}

SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	for (auto&& stage : playStage_)
	{
		Vector2 pos = stage->GetOffset();
		DrawGraph(pos.x,pos.y,stage->GetStageDraw(),true);
	}
	ScreenFlip();
}

bool SceneMng::Init(void)
{
	SetGraphMode(1280, 720, 16);
	ChangeWindowMode(true);
	SetWindowText("Ç’ÇÊÇ’ÇÊ");
	SetDrawScreen(DX_SCREEN_BACK);						//  ﬁØ∏ ﬁØÃßÇ…ê›íË
	if (DxLib_Init() == -1)
	{
		return false;
	}
	frame_ = 0;

	playStage_.emplace_back(std::make_unique<Stage>(std::move(Vector2( 60, 48 )), std::move(Vector2(288, 576))));
	playStage_.emplace_back(std::make_unique<Stage>(std::move(Vector2(700, 48 )), std::move(Vector2(288, 576))));

	return false;
}
