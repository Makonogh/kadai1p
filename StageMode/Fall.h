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
		
		bool EraseFlag = true;						// �폜Ӱ�ނɈڍs���邩�̃t���O
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
			stage.playUnit_->StartVive(200, 100);
			stage.stagemode_ = StageMode::Puyon;
		}
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)			// �f�[�^�Ɋi�[
			{
				stage.SetPermition(puyo);
				if (!puyo->GetDirPermit().perBit.d)
				{
					Vector2 vec = puyo->GetGrid(stage.blockSize_);
					puyo->ChangeSpeed(6);
					puyo->SetLead(0);
					stage.data_[vec.x][vec.y] = puyo;
					puyo->SetPos({ (vec.x - 1) * stage.blockSize_,(vec.y - 1) * stage.blockSize_ });
				}
			}
		);

	}
};