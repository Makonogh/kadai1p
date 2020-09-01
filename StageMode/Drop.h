#pragma once
#include "../Stage.h"


struct Drop
{
	void operator() (Stage& stage)
	{
		stage.playUnit_->Update();						// ‘€ìˆ—
		stage.stageAct_[StageMode::Fall](stage);		// —‰ºˆ—
	}
};
