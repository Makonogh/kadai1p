#pragma once
#include "../Stage.h"

struct Munyon
{
	void operator() (Stage& stage)
	{
		bool flag = false;
		for (auto puyo : stage.puyoVec_)
		{
			//puyo->Update(0);
			//flag |= puyo->CheckMuyon();
		}
		if (!flag)
		{
			if (stage.ojamaList_.size() > 0)
			{
				int count = 12;
				for (auto ojama : stage.ojamaList_)
				{
					stage.OjamaInstance(ojama);
					count--;
					if (count <= 0)
					{
						break;
					}
				}
				stage.ojamaList_.erase();
			}
			else
			{
				stage.PuyoInstance();
				stage.SetPermition(stage.puyoVec_[0]);
				stage.stagemode_ = StageMode::Drop;
			}
		}
	}
};