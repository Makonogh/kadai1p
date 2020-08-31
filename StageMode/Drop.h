#pragma once
#include "../Stage.h"


struct Drop
{
	void operator() (Stage& stage)
	{
	/*	std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
			{
				stage.SetPermition(puyo);
			}
		);*/
		
		
		stage.stageAct_[StageMode::Fall](stage);
		stage.playUnit_->Update();
		

		//bool EraseFlag = false;						// íœÓ°ÄŞ‚ÉˆÚs‚·‚é‚©‚Ìƒtƒ‰ƒO
		//std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
		//	{
		//		if (!puyo->Update())
		//		{
		//			EraseFlag = true;
		//		}
		//	}
		//);

		//if (EraseFlag == false)
		//{
		//	auto vec1 = stage.puyoVec_[0]->GetGrid(stage.blockSize_);
		//	auto vec2 = stage.puyoVec_[1]->GetGrid(stage.blockSize_);
		//	stage.data_[vec1.x][vec1.y] = stage.puyoVec_[0];
		//	stage.data_[vec2.x][vec2.y] = stage.puyoVec_[1];
		//	stage.stagemode_ = StageMode::Erase;
		//}
	}
};
