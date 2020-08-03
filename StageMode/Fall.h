#pragma once
#include "../Stage.h"

struct Fall
{
	void operator() (Stage& stage)
	{
		stage.stagemode_ = StageMode::Fall;
	}
};