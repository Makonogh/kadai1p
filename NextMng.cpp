#include "NextMng.h"
#include <DxLib.h>
#include "_debug/_DebugConOut.h"

NextMng::NextMng(Vector2 pos,int size,int id)
{
	Init(pos,size,id);
}

NextMng::~NextMng()
{
}

int NextMng::GetScreenID()
{
	return screenID_;
}

Vector2 NextMng::GetPos()
{
	return pos_;
}

PairPuyo NextMng::TakePuyo()
{
	return {puyoList_[0],puyoList_[1]};
}

void NextMng::UpDateList()
{
	TRACE("%d", puyoList_.size());
	puyoList_.erase(puyoList_.begin(), puyoList_.begin() + 2);
	auto id = static_cast<PuyoType>(GetRand(4));
	puyoList_.emplace_back(std::make_shared<Puyo>(Vector2(0, 0), id));
	id = static_cast<PuyoType>(GetRand(4));
	puyoList_.emplace_back(std::make_shared<Puyo>(Vector2(0, 0), id));
	for (int x = 0; x < 4; x++)
	{
		puyoList_[x]->SetPos({ blockSize_ * (x / 2),blockSize_ * ((x / 2) + ((x + 1) % 2)) });
	}
	TRACE("%d", puyoList_.size());
}

void NextMng::Init(Vector2 pos,int size,int id)
{
	blockSize_ = size;
	size_ = {size * 1.5,size * 3.0};
	screenID_ = MakeScreen(size_.x ,size_.y,true);
	nextMax_ = 80;
	pos_ = pos;
	id_ = id;
	
	puyoList_.reserve(nextMax_);
	for (int x = 0; x < nextMax_;x++)
	{
		auto id = static_cast<PuyoType>(GetRand(4));
		puyoList_.emplace_back(std::make_shared<Puyo>(Vector2(0,0), id));
	}
	//for (int x = 0;x < 4;x++)
	//{
	//	puyoList_[x]->SetPos({blockSize_ * (x / 2 ),blockSize_ * ((x + 1) % 2) - blockSize_});
	//}
	TRACE("%d", puyoList_.size());
}

void NextMng::Draw()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
	for (int x = 0; x < 4; x++)
	{
		puyoList_[x]->Draw();
	}
}
