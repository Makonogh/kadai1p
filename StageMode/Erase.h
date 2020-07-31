#pragma once
#include "../Stage.h"

struct Erase
{
	void operator() (Stage& stage)
	{
		bool delFlag = false;
		for (auto&& droped : stage.puyoVec_)
		{
			delFlag |= EraseSet(stage);
		}
		if (delFlag)
		{
			ErasePuyo(stage);
		}
		else
		{
			stage.PuyoInstance();
			stage.stagemode_ = StageMode::Drop;
			/*stage.stagemode_ = StageMode::Fall;*/
		}
	}

	bool EraseSet(Stage& stage)
	{
		memset(stage.eraseBaseData_.data(), 0, stage.eraseBaseData_.size() * sizeof(PuyoType));
		auto vec = stage.puyoVec_[0]->GetGrid(stage.blockSize_);
		for (auto&& puyo:stage.eraseBaseData_)
		{
			puyo.reset();
		}
		int count = 0;
		std::function<void(PuyoType, Vector2)> checkPuyo = [&](PuyoType id, Vector2 vec) {
			if (stage.eraseData_[vec.x][vec.y])
			{
				if (stage.data_[vec.x][vec.y]->GetPuyoID() == id)
				{
					count++;
					checkPuyo(id, { vec.x + 1,vec.y });
					checkPuyo(id, { vec.x - 1,vec.y });
					checkPuyo(id, { vec.x ,vec.y + 1 });
					checkPuyo(id, { vec.x ,vec.y - 1 });
				}
			};
		};

		checkPuyo(stage.puyoVec_[0]->GetPuyoID(), vec);

		if (count < 4)
		{
			for (auto&& puyo : stage.eraseBaseData_)
			{
				puyo.reset();
			}
			return false;
		}
		else
		{
			for (auto&& puyo : stage.puyoVec_)
			{
				auto pos = puyo->GetGrid(stage.blockSize_);

				if (stage.eraseData_[pos.y][pos.x])
				{
					puyo->SetAlive(false);
					stage.data_[pos.y][pos.x].reset();
				}
			}
			return true;
		}
	}

	bool ErasePuyo(Stage& stage)
	{
		auto itr = std::remove_if(stage.puyoVec_.begin(), stage.puyoVec_.end(), [](auto&& puyo) {return !(puyo->GetAlive()); });
		stage.puyoVec_.erase(itr, stage.puyoVec_.end());
		return false;
	}
};

