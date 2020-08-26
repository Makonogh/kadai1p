#pragma once
#include "../Stage.h"

struct Erase
{
	void operator() (Stage& stage)
	{
		bool delFlag = false;
		for (auto&& puyo : stage.puyoVec_)
		{
			delFlag |= EraseSet(stage,puyo);
			puyo->DethCount();
		}
		if (delFlag)
		{
			if (ErasePuyo(stage))
			{
				std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
					{
						auto pos = puyo->GetGrid(stage.blockSize_);
						stage.data_[pos.x][pos.y].reset();
						stage.SetPermition(puyo);
					}
				);
				stage.playUnit_->StartVive(1000,1000);
				stage.stagemode_ = StageMode::Fall;
			}
		}
		else
		{
			stage.PuyoInstance();
			stage.stagemode_ = StageMode::Drop;
		}
	}

	bool EraseSet(Stage& stage,std::shared_ptr<Puyo> puyo)
	{
		memset(stage.eraseBaseData_.data(), 0, stage.eraseBaseData_.size() * sizeof(PuyoType));
		auto vec = puyo->GetGrid(stage.blockSize_);
		for (auto&& Epuyo:stage.eraseBaseData_)
		{
			Epuyo.reset();
		}
		int count = 0;
		std::function<void(PuyoType, Vector2)> checkPuyo = [&](PuyoType id, Vector2 vec) {
			if (!stage.eraseData_[vec.x][vec.y])
			{
				if (stage.data_[vec.x][vec.y])
				{
					if (stage.data_[vec.x][vec.y]->GetPuyoID() == id)
					{
						count++;
						stage.eraseData_[vec.x][vec.y] = stage.data_[vec.x][vec.y];
						checkPuyo(id, { vec.x + 1,vec.y });
						checkPuyo(id, { vec.x - 1,vec.y });
						checkPuyo(id, { vec.x ,vec.y + 1 });
						checkPuyo(id, { vec.x ,vec.y - 1 });
					}
				}
			};
		};

		checkPuyo(puyo->GetPuyoID(), vec);

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
				if (stage.eraseData_[pos.x][pos.y])
				{
					puyo->SetAlive(false);
				}
			}
			return true;
		}
	}

	bool ErasePuyo(Stage& stage)
	{
		bool erase = false;
		for (auto data : stage.puyoVec_)
		{
			auto pos = data->GetGrid(stage.blockSize_);
			if (!data->GetAlive())
			{
				erase = true;
				stage.data_[pos.x][pos.y].reset();
				lpEff.playList_.push_back({ "”j‰ó", stage.GetWorPos({data->GetPos().x + stage.blockSize_ / 2,data->GetPos().y + stage.blockSize_}) });
			}
		}
		auto itr = std::remove_if(stage.puyoVec_.begin(), stage.puyoVec_.end(), [](auto&& puyo) {return !(puyo->GetAlive()); });
		
		stage.puyoVec_.erase(itr, stage.puyoVec_.end());

		return erase;
	}
};

