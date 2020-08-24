#pragma once
#include "../Stage.h"

struct Fall
{
	void operator() (Stage& stage)
	{
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
			{
				stage.SetPermition(puyo);
			}
		);
		
		bool EraseFlag = true;						// 削除ﾓｰﾄﾞに移行するかのフラグ
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
			{
				if (!puyo->Update())
				{
					EraseFlag = false;
				}
			}
		);

		if (EraseFlag)
		{
			stage.stagemode_ = StageMode::Erase;
		}
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)			// データに格納
			{
				if (!puyo->GetDirPermit().perBit.d )
				{
					puyo->ChangeSpeed(6);
					Vector2 vec = puyo->GetGrid(stage.blockSize_);
					puyo->SetPos({ (vec.x - 1) * stage.blockSize_,(vec.y - 1) * stage.blockSize_ });
					stage.data_[vec.x][vec.y] = puyo;
				}
			}
		);
	}
};