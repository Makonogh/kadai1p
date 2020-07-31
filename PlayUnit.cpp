#include "PlayUnit.h"
#include "input/Controller.h"
#include "Stage.h"
#include "_debug/_DebugConOut.h"

PlayUnit::PlayUnit(Stage& stage):stage_(stage)
{
	Init();
}

PlayUnit::~PlayUnit()
{
}

bool PlayUnit::Update()
{
	auto CntData = stage_.controller_->GetCntData();
	for (auto data : InputID())
	{
		

		KeyAct[data](CntData);
	}

	return false;
}

bool PlayUnit::Init()
{
	targetID_ = 0;
	KeyAct.try_emplace(InputID::UP, [&](CntData cntData)
		{
			if (cntData[InputID::UP][static_cast<int>(Trg::Now)] && !cntData[InputID::UP][static_cast<int>(Trg::Old)])
			{
				stage_.puyoVec_[0]->Move(InputID::UP);
				stage_.puyoVec_[1]->Move(InputID::UP);
			}
		}
	);
	KeyAct.try_emplace(InputID::DOWN, [&](CntData cntData)
		{
			if (cntData[InputID::DOWN][static_cast<int>(Trg::Now)])
			{
				TRACE("%d", cntData[InputID::DOWN][static_cast<int>(Trg::Now)]);
				stage_.puyoVec_[0]->SoftDrop();
				stage_.puyoVec_[1]->SoftDrop();
			}
		}
	);
	KeyAct.try_emplace(InputID::LEFT, [&](CntData cntData)
		{
			if (cntData[InputID::LEFT][static_cast<int>(Trg::Now)] && !cntData[InputID::LEFT][static_cast<int>(Trg::Old)])
			{
				stage_.puyoVec_[0]->Move(InputID::LEFT);
				stage_.puyoVec_[1]->Move(InputID::LEFT);
			}
		}
	);
	KeyAct.try_emplace(InputID::RIGHT, [&](CntData cntData)
		{
			if (cntData[InputID::RIGHT][static_cast<int>(Trg::Now)] && !cntData[InputID::RIGHT][static_cast<int>(Trg::Old)])
			{
				stage_.puyoVec_[0]->Move(InputID::RIGHT);
				stage_.puyoVec_[1]->Move(InputID::RIGHT);
			}
		}
	);
	KeyAct.try_emplace(InputID::BT1, [&](CntData cntData)
		{
			if (cntData[InputID::BT1][static_cast<int>(Trg::Now)] && !cntData[InputID::BT1][static_cast<int>(Trg::Old)])
			{
				RotPuyo(stage_.puyoVec_[targetID_]->GetPos(), stage_.puyoVec_[targetID_^1]->GetPos(),true);
			}
		}
	);
	KeyAct.try_emplace(InputID::BT2, [&](CntData cntData)
		{
			if (cntData[InputID::BT2][static_cast<int>(Trg::Now)] && !cntData[InputID::BT2][static_cast<int>(Trg::Old)])
			{
				RotPuyo(stage_.puyoVec_[targetID_]->GetPos(), stage_.puyoVec_[targetID_ ^ 1]->GetPos(), false);
			}
		}
	);

	return false;
}

void PlayUnit::RotPuyo(Vector2 vec1, Vector2 vec2, bool Rotate)
{
	auto MoveLen = stage_.blockSize_;
	// Rotate true::ŽžŒv‰ñ‚è false::”¼ŽžŒv‰ñ‚è
	if (Rotate)
	{
		MoveLen = -MoveLen;
	}

	if (vec1.y < vec2.y)
		// ã‚É‚¢‚é‚Æ‚«
	{
		stage_.puyoVec_[targetID_ ^ 1]->SetPos({ stage_.puyoVec_[targetID_]->GetPos().x + MoveLen , stage_.puyoVec_[targetID_]->GetPos().y});
	}
	if (vec1.y > vec2.y)
		// ‰º‚É‚¢‚é‚Æ‚«
	{
		stage_.puyoVec_[targetID_ ^ 1]->SetPos({ stage_.puyoVec_[targetID_]->GetPos().x - MoveLen , stage_.puyoVec_[targetID_]->GetPos().y});
	}
	if (vec1.x < vec2.x)
		// ‰E‚É‚¢‚é‚Æ‚«
	{
		stage_.puyoVec_[targetID_ ^ 1]->SetPos({ stage_.puyoVec_[targetID_]->GetPos().x , stage_.puyoVec_[targetID_]->GetPos().y - MoveLen});
	}
	if (vec1.x > vec2.x)
		// ¶‚É‚¢‚é‚Æ‚«
	{
		stage_.puyoVec_[targetID_ ^ 1]->SetPos({ stage_.puyoVec_[targetID_]->GetPos().x, stage_.puyoVec_[targetID_]->GetPos().y + MoveLen });
	}

	if (stage_.puyoVec_[targetID_]->GetPos().y > stage_.puyoVec_[targetID_ ^ 1]->GetPos().y)
	{
		std::swap(stage_.puyoVec_[targetID_], stage_.puyoVec_[targetID_ ^ 1]);
		targetID_ ^= 1;
	}
}
