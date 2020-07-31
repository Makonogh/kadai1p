#pragma once
#include "../Stage.h"


struct Drop
{
	void operator() (Stage& stage) 
	{
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
			{
				stage.SetPermition(puyo);
			}
		);

		stage.playUnit_->Update();

		bool rensaFlag = true;
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
			{
				if (!puyo->Update())
				{
					auto vec = stage.puyoVec_[0]->GetGrid(stage.blockSize_);
					stage.data_[vec.x][vec.y] = stage.puyoVec_[0];
					stage.data_[vec.x][vec.y] = stage.puyoVec_[1];
					stage.stagemode_ = StageMode::Erase;
				}
			}
		);
	}
};
