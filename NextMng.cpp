#include "NextMng.h"
#include <DxLib.h>


NextMng::NextMng(Vector2 pos,Vector2 size)
{
	Init(pos,size);
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

void NextMng::Init(Vector2 pos,Vector2 size)
{
	screenID_ = MakeScreen(size_.x ,size.y,true);
	nextMax_ = 800;
	pos_ = pos;
	size_ = size;
}

void NextMng::Draw()
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawBox(0, 0, size_.x, size_.y, 0xffffff, false);
}
