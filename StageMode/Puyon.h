#pragma once
#include "../Stage.h"

struct Puyon
{
	void operator() (Stage &stage)
	{
		stage.stagemode_ = StageMode::Munyon;
	}
};