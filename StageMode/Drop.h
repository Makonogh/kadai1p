#pragma once
#include "../Stage.h"


struct Drop
{
	void operator() (Stage& stage)
	{
		stage.playUnit_->Update();						// 操作処理
		stage.stageAct_[StageMode::Fall](stage);		// 落下処理
	}
};
