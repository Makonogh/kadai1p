#pragma once
#include "../Stage.h"

struct Drop
{
	void operator() (Stage& stage)
	{
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::unique_ptr<Puyo>& puyo)
			{
				stage.SetPermition(puyo);
			}
		);

		stage.playUnit_->Update();

		bool rensaFlag = true;
		std::for_each(stage.puyoVec_.rbegin(), stage.puyoVec_.rend(), [&](std::unique_ptr<Puyo>& puyo)
			{
				if (!puyo->Update())
				{
					rensaFlag = false;
				}
			}
		);
	}
};
