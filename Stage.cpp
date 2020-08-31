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
#include "SceneMng.h"

#include "StageMode/Drop.h"
#include "StageMode/Erase.h"
#include "StageMode/Munyon.h"
#include "StageMode/Puyon.h"
#include "StageMode/Fall.h"

int Stage::stageCount_ = 0;
Stage::Stage(Vector2&& offset,Vector2&& size)
{
	id_ = stageCount_;
	pos_ = offset;
	size_ = size;
	blockSize_ = size.x / (STAGE_CHIP_X - 2);
	fieldSize_ = { lpSceneMng.screenSize_.x / 2,lpSceneMng.screenSize_.y };
	fieldPos_ = { id_ * fieldSize_.x,0 };
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

std::pair<int, Vector2> Stage::GetNextScreen()
{
	return { NextList_->GetScreenID(), NextList_->GetPos()};
}

const Vector2& Stage::GetOffset(void)
{
	return fieldPos_;
}

void Stage::Draw(void)
{
	SetDrawScreen(stageID_);
	ClsDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 240);		//ブレンドモード
	DrawBox(0, 0, size_.x, size_.y, 0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	std::for_each(puyoVec_.rbegin(), puyoVec_.rend(), [&](std::shared_ptr<Puyo>& puyo)
		{
			puyo->Draw();
		}
	);
	DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
	SetDrawScreen(ojamaID_);
	ClsDrawScreen();

	std::size_t size = ojamaList_.size();

	for (unsigned int t = 0; t < size; t++)
	{
		DrawCircle(blockSize_ / 2 + blockSize_ * (t % 7), blockSize_ / 2, blockSize_ / 2, 0xffffff, true);
	}

	NextList_->Draw();

	SetDrawScreen(screenID_);
	ClsDrawScreen();
	Vector2 NePos = NextList_->GetPos();
	int NeID = NextList_->GetScreenID();
	DrawGraph(pos_.x, pos_.y, stageID_, true);
	DrawGraph(pos_.x , pos_.y - blockSize_, ojamaID_, true);
	DrawGraph(NePos.x, NePos.y, NeID, true);
	
}

void Stage::Update(void)
{
	(*controller_)();
	
	stageAct_[stagemode_](*this);

	Draw();
}

Vector2 Stage::GetWorPos(Vector2 pos)
{
	return pos + pos_ + fieldPos_;
}

bool Stage::Init(void)
{
	screenID_ = MakeScreen(fieldSize_.x, fieldSize_.y, true);
	stageID_ = MakeScreen(size_.x, size_.y, true);
	ojamaID_ = MakeScreen(size_.x, blockSize_, true);
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
	
	NextList_ = std::make_unique<NextMng>(Vector2( pos_.x + size_.x + blockSize_,pos_.y + blockSize_ ),blockSize_,id_);
	PuyoInstance();

	SetGamePad();
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
	puyoVec_.emplace(puyoVec_.begin(), NextList_->TakePuyo().first);
	puyoVec_.emplace(puyoVec_.begin() + 1, NextList_->TakePuyo().second);
	NextList_->UpDateList();
	puyoVec_[0]->SetPos({ blockSize_ * 3 ,0 });
	puyoVec_[1]->SetPos({ blockSize_ * 3 ,blockSize_});
	
	puyoVec_[0]->SetLead(1);
	puyoVec_[1]->SetLead(2);
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

void Stage::GetSpuyo()
{
	int spos1 = 0;
	int spos2 = 0;
	Vector2 pos1 = puyoVec_[0]->GetGrid(blockSize_);
	Vector2 pos2 = puyoVec_[1]->GetGrid(blockSize_);
	
	for (int p = pos1.y;p <= STAGE_CHIP_Y;p++)
	{
		if (data_[pos1.x][p + 1])
		{
			spos1 = p;
			break;
		}
	}
	for (int p = pos2.y; p <= STAGE_CHIP_Y; p++)
	{
		if (data_[pos2.x][p + 1])
		{
			spos2 = p;
			break;
		}
	}
	if (pos1.x == pos2.x)
	{
		if (pos1.y > pos2.y)
		{
			spos2--;
		}
		else
		{
			spos1--;
		}
	}
	puyoVec_[0]->SetSpos(spos1);
	puyoVec_[1]->SetSpos(spos2);
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
