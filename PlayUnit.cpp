#include "PlayUnit.h"
#include "input/Controller.h"
#include "input/KeyInput.h"
#include "input/GamePad.h"
#include "Stage.h"
#include "_debug/_DebugConOut.h"
#include "Puyo/OjamaPuyo.h"
#include "DxLib.h"

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
	stage_.GetSpuyo();
	if (CheckBady(0, !stage_.puyoVec_[0 ^ 1]->GetDirPermit().perBit.d) || CheckBady(1, !stage_.puyoVec_[1 ^ 1]->GetDirPermit().perBit.d))
	{
		targetID_ = 0;	
		return true;
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
				//stage_.puyoVec_[0]->Move(InputID::UP);
				//stage_.puyoVec_[1]->Move(InputID::UP);
			}
		}
	);
	KeyAct.try_emplace(InputID::DOWN, [&](CntData cntData)
		{
			if (cntData[InputID::DOWN][static_cast<int>(Trg::Now)])
			{
				stage_.puyoVec_[0]->SoftDrop();
				stage_.puyoVec_[1]->SoftDrop();
			}
		}
	);
	KeyAct.try_emplace(InputID::LEFT, [&](CntData cntData)
		{
			if (cntData[InputID::LEFT][static_cast<int>(Trg::Now)] && !cntData[InputID::LEFT][static_cast<int>(Trg::Old)])
			{
				if (stage_.puyoVec_[0 ^ 1]->GetDirPermit().perBit.l&&stage_.puyoVec_[1 ^ 1]->GetDirPermit().perBit.l)
				{
					stage_.puyoVec_[0]->Move(InputID::LEFT);
					stage_.puyoVec_[1]->Move(InputID::LEFT);
				}
			}
		}
	);
	KeyAct.try_emplace(InputID::RIGHT, [&](CntData cntData)
		{
			if (cntData[InputID::RIGHT][static_cast<int>(Trg::Now)] && !cntData[InputID::RIGHT][static_cast<int>(Trg::Old)])
			{
				if (stage_.puyoVec_[0 ^ 1]->GetDirPermit().perBit.r && stage_.puyoVec_[1 ^ 1]->GetDirPermit().perBit.r)
				{
					stage_.puyoVec_[0]->Move(InputID::RIGHT);
					stage_.puyoVec_[1]->Move(InputID::RIGHT);
				}
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
	KeyAct.try_emplace(InputID::BT3, [&](CntData cntData)
		{
			if (cntData[InputID::BT3][static_cast<int>(Trg::Now)] && !cntData[InputID::BT3][static_cast<int>(Trg::Old)])
			{
				stage_.ojamaList_.emplace_back
				(std::make_shared<OjamaPuyo>(Vector2(0 + (stage_.ojamaList_.size() % 7 ) * stage_.blockSize_,0 + (stage_.ojamaList_.size() / 7)), PuyoType::OJAMA));
			}
		}
	);
	KeyAct.try_emplace(InputID::BT4, [&](CntData cntData)
		{
			if (cntData[InputID::BT4][static_cast<int>(Trg::Now)] && !cntData[InputID::BT4][static_cast<int>(Trg::Old)])
			{
				if (stage_.controller_->GetType() == ContType::KeyBoard )
				{
					stage_.SetGamePad();
					return;
				}
				if (stage_.controller_->GetType() == ContType::GamePad)
				{
					stage_.SetKeyInput();
					return;
				}
			}
		}
	);
	return false;
}

void PlayUnit::StartVive(int pow,int time)
{
	if (stage_.controller_->GetType() == ContType::GamePad)
	{
		StopJoypadVibration(stage_.controller_->GetID());
		StartJoypadVibration(stage_.controller_->GetID(), pow, time);
	}
}

void PlayUnit::RotPuyo(Vector2 vec1, Vector2 vec2, bool Rotate)
{
	auto MoveLen = stage_.blockSize_;
	Vector2 RotPos;
	// Rotate true::ŽžŒv‰ñ‚è false::”¼ŽžŒv‰ñ‚è
	if (Rotate)
	{
		MoveLen = -MoveLen;
	}

	if (vec1.y < vec2.y)
		// ã‚É‚¢‚é‚Æ‚«
	{
		RotPos = { stage_.puyoVec_[targetID_]->GetPos().x + MoveLen , stage_.puyoVec_[targetID_]->GetPos().y};
	}
	if (vec1.y > vec2.y)
		// ‰º‚É‚¢‚é‚Æ‚«
	{
		RotPos = { stage_.puyoVec_[targetID_]->GetPos().x - MoveLen , stage_.puyoVec_[targetID_]->GetPos().y};
	}
	if (vec1.x < vec2.x)
		// ‰E‚É‚¢‚é‚Æ‚«
	{
		RotPos = { stage_.puyoVec_[targetID_]->GetPos().x , stage_.puyoVec_[targetID_]->GetPos().y - MoveLen};
	}
	if (vec1.x > vec2.x)
		// ¶‚É‚¢‚é‚Æ‚«
	{
		RotPos = { stage_.puyoVec_[targetID_]->GetPos().x, stage_.puyoVec_[targetID_]->GetPos().y + MoveLen };
	}

	if (stage_.puyoVec_[targetID_]->GetPos().y < stage_.puyoVec_[targetID_ ^ 1]->GetPos().y)
	{
		std::swap(stage_.puyoVec_[targetID_], stage_.puyoVec_[targetID_ ^ 1]);
		targetID_ ^= 1;
	}

	if (CheckMove(stage_.GetGrid(RotPos)))
	{
		stage_.puyoVec_[targetID_ ^ 1]->SetPos(RotPos);
	}
}

bool PlayUnit::CheckMove(Vector2 vec)
{
	if (stage_.data_[vec.x][vec.y])
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool PlayUnit::CheckBady(int id, int bit)
{
	if (bit)
	{
		stage_.puyoVec_[id]->ChangeSpeed(6);
		stage_.puyoVec_[id]->SetLead(0);
		stage_.stagemode_ = StageMode::Fall;
		return true;
	}
	return false;
}
