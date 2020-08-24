#include "Stage.h"
#include <DxLib.h>
#include <algorithm>
#include "Input/KeyInput.h"
#include "Input/GamePad.h"
#include "common/Vector2.h"
#include <functional>
#include "PlayUnit.h"
#include "Puyo/OjamaPuyo.h"
#include "Effect.h"

#include "StageMode/Drop.h"
#include "StageMode/Erase.h"
#include "StageMode/Munyon.h"
#include "StageMode/Puyon.h"
#include "StageMode/Fall.h"

int Stage::stageCount_ = 0;
Stage::Stage(Vector2&& offset,Vector2&& size)
{
	id_ = stageCount_;
	Stage::offset_ = offset;
	Stage::size_ = size;
	blockSize_ = size.x / (STAGE_CHIP_X - 2);
	stageCount_++;
	Init();
}

Stage::~Stage()
{
	stageCount_--;
}

int Stage::GetStageDraw(void)
{
	return screenID_;
}

const Vector2& Stage::GetOffset(void)
{
	return offset_;
}

void Stage::Draw(void)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawBox(0, 0,  size_.x, size_.y, 0xffffff, false);

	for (int x = 1; x <= 11; x++)
	{
		DrawLine(0,  blockSize_ * x, size_.x, blockSize_ * x, 0xffffff, false);
	}
	for (int x = 1; x <= 5; x++)
	{
		DrawLine(blockSize_ * x, 0, blockSize_ * x, size_.y, 0xffffff, false);
	}
	std::size_t size = ojamaList_.size();
	
	for (unsigned int t = 0; t <size; t++)
	{
		DrawCircle(blockSize_ / 2 + blockSize_ * (t % 7), blockSize_ / 2, blockSize_ / 2, 0xffffff, true);
	}
	for (auto&& puyo : puyoVec_)
	{
		puyo->Draw();
	}
	DrawFormatString(blockSize_ / 2, blockSize_ / 2, 0x000000, "%d", size);
}

void Stage::Update(void)
{
	(*controller_)();
	
	stageAct_[stagemode_](*this);
	//std::for_each(puyoVec_.rbegin(), puyoVec_.rend(), [&](std::unique_ptr<Puyo>& puyo)
	//	{
	//		SetPermition(puyo);
	//	}
	//);
	//playUnit_->Update();
	//bool rensaFlag = true;
	//std::for_each(puyoVec_.rbegin(), puyoVec_.rend(), [&](std::unique_ptr<Puyo>& puyo)
	//	{
	//		if (!puyo->Update())
	//		{
	//			rensaFlag = false;
	//		}
	//	}
	//);
	/*if (rensaFlag)
	{
		stagemode_ = StageMode::RENSA;
	}

	if (stagemode_ == StageMode::RENSA)
	{

	}*/
	/*if (!(puyoVec_[0]->Update()))
	{
		auto vec = puyoVec_[0]->GetGrid(blockSize_);
		data_[vec.x][vec.y] = puyoVec_[0]->GetPuyoID();
		EraseSet();
		for (auto&& puyo: puyoVec_)
		{
			auto pos = puyo->GetGrid(blockSize_);
			if (eraseData_[pos.x][pos.y] != PuyoType::NON)
			{
				puyo->SetAlive(false);
				data_[pos.x][pos.y] = PuyoType::NON;
			}
		}
	}*/
	/*PuyoInstance();*/
	Draw();
}

Vector2 Stage::GetWorPos(Vector2 pos)
{
	return pos + offset_;
}

bool Stage::Init(void)
{
	screenID_ = MakeScreen(size_.x, size_.y, true);
	baseData_.resize(STAGE_CHIP_X* STAGE_CHIP_Y );
	eraseBaseData_.resize(STAGE_CHIP_X * STAGE_CHIP_Y);

	for (int no = 0; no < STAGE_CHIP_X ; no++)
	{
		data_.emplace_back(&baseData_[no * STAGE_CHIP_Y ]);
		eraseData_.emplace_back(&eraseBaseData_[no * STAGE_CHIP_Y]);
	}
	for (int no = 0; no < STAGE_CHIP_X * STAGE_CHIP_Y;no++)
	{
		baseData_[no].reset();
	}
	for (int no = 0; no < STAGE_CHIP_X; no++)
	{
		data_[no][0] = std::make_shared<Puyo>(Vector2(blockSize_ * no, 0), PuyoType::WALL); //PuyoType::WALL;
		data_[no][STAGE_CHIP_Y - 1] = std::make_shared<Puyo>(Vector2(blockSize_ * no, STAGE_CHIP_Y - 1), PuyoType::WALL);
	}
	for (int no = 0; no < STAGE_CHIP_Y; no++)
	{
		data_[0][no] = std::make_shared<Puyo>(Vector2(0, blockSize_ * no), PuyoType::WALL);;
		data_[STAGE_CHIP_X - 1][no] = std::make_shared<Puyo>(Vector2( 0,blockSize_ * no), PuyoType::WALL);;
	}
	
	
	PuyoInstance();

	controller_ = std::make_unique<KeyInput>();
	controller_->Setup(id_);
	playUnit_ = std::make_unique<PlayUnit>(*this);
	stagemode_ = StageMode::Drop;
	stageAct_.try_emplace(StageMode::Drop, Drop());
	stageAct_.try_emplace(StageMode::Erase, Erase());
	stageAct_.try_emplace(StageMode::Fall, Fall());
	stageAct_.try_emplace(StageMode::Munyon, Munyon());
	stageAct_.try_emplace(StageMode::Puyon, Puyon());

	
	return false;
}

bool Stage::PuyoInstance()
{
	auto id = static_cast<PuyoType>(GetRand(4));
	puyoVec_.emplace(puyoVec_.begin(), std::make_shared<Puyo>(Vector2(blockSize_ * 4, 0), id));
	id = static_cast<PuyoType>(GetRand(4));
	puyoVec_.emplace(puyoVec_.begin() + 1, std::make_shared<Puyo>(Vector2(blockSize_ * 4, blockSize_), id));
	SetPermition(puyoVec_[0]);
	SetPermition(puyoVec_[1]);
	return false;
}

bool Stage::OjamaInstance(std::shared_ptr<Puyo>& puyo)
{
	puyoVec_.emplace(puyoVec_.begin(),std::make_shared<OjamaPuyo>(puyo->GetPos(),PuyoType::OJAMA));
	return false;
}

bool Stage::SetPermition(std::shared_ptr<Puyo>& puyo)
{
	DirPermit dirPermit;
	dirPermit = { 1,1,1,1 };
	Vector2 pos = puyo->GetGrid(blockSize_);
	if (data_[pos.x - 1][pos.y])
	{
		dirPermit.perBit.l = 0;
	}
	if (data_[pos.x + 1][pos.y])
	{
		dirPermit.perBit.r = 0;
	}
	if (data_[pos.x][pos.y - 1])
	{
		dirPermit.perBit.u = 0;
	}
	if (data_[pos.x][pos.y + 1])
	{
		dirPermit.perBit.d = 0;
	}
	puyo->SetDirPermit(dirPermit);
	return true;
}

void Stage::SetGamePad()
{
	controller_.reset();
	controller_ = std::make_unique<GamePad>();
	controller_->Setup(id_);
}

void Stage::SetKeyInput()
{
	controller_.reset();
	controller_ = std::make_unique<KeyInput>();
	controller_->Setup(id_);
}

Vector2 Stage::GetGrid(Vector2 pos)
{
	return Vector2(pos.x / blockSize_ + 1, pos.y / blockSize_ + 1);
}
