#pragma once
#include "../Stage.h"


struct Drop
{
	void operator() (Stage& stage)
	{
		stage.playUnit_->Update();						// ���쏈��
		stage.stageAct_[StageMode::Fall](stage);		// ��������
	}
};
