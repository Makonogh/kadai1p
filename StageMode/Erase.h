#pragma once

struct Erase
{
	void operator() (Stage& stage)
	{
		bool delFlag = false;
		for (auto&& droped : stage.puyoVec)
		{
			delFlag |= CheckErasePuyo()
		}
		if (delFlag)
		{
			ErasePuyo(stage);
		}
	}
};