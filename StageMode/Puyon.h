#pragma once
#include "../Stage.h"

struct Puyon
{
	void operator() (Stage &stage)
	{
		Vector2 Gpos = {0,0};			// これは起点となる座標の保存用
		for(auto puyo:stage.puyoVec_)
		{
			if (puyo->GetGround())
			{
				auto vec = puyo->GetGrid(stage.blockSize_);
				Gpos = puyo->GetPos();
				std::function<void(Vector2)> checkPuyon = [&](Vector2 pos) {
					if (stage.data_[pos.x][pos.y])
					{
						stage.data_[pos.x][pos.y]->SetPuyon(true);
						checkPuyon({ pos.x, pos.y - 1 });
					}
				};
				checkPuyon({ vec.x ,vec.y - 1 });
				break;
			}	
		}
		bool MunyonFlag = true;						// ﾓｰﾄﾞに移行するかのフラグ

		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
			{
				if (puyo->PuyonUpdate(Gpos))
				{
					MunyonFlag = false;
				}
			}
		);

		if (MunyonFlag)
		{
			stage.stagemode_ = StageMode::Erase;
		}
	}
};