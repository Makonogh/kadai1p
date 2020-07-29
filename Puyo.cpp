#include "Puyo.h"
#include "DxLib.h"

Puyo::Puyo(PuyoType type):size_(48)
{
	pos_.y = 0;
	pos_.x = size_ * 3;
	type_ = type;
	alive_ = true;
	Init();
}

Puyo::~Puyo()
{
}

bool Puyo::Update()
{
	puyoFrame_++;
	if (dirPermit_.perBit.d == 1)
	{
		if (puyoFrame_ % dropSpeed_ == 0)
		{
			pos_.y ++;
			return true;
		}
	}
	return false;
}

void Puyo::Move(InputID id)
{
	switch (id)
	{
	case InputID::UP:
		if (dirPermit_.perBit.u == 1)
		{
			pos_.y -= size_;
		}
		break;
	case InputID::DOWN:
	/*	if (dirPermit_.perBit.d == 1)
		{
			pos_.y += size_;
			SoftDrop();
		}*/
		break;
	case InputID::LEFT:
		if (dirPermit_.perBit.l == 1)
		{
			pos_.x -= size_;
		}
		break;
	case InputID::RIGHT:
		if (dirPermit_.perBit.r == 1)
		{
			pos_.x += size_;
		}
		break;
	default:
		break;
	}
}

void Puyo::SetDirPermit(DirPermit DirPermit)
{
	dirPermit_ = DirPermit;
}

const Vector2 Puyo::GetGrid(int size)
{
	return Vector2(pos_.x / size + 1,pos_.y /size + 1);
}

PuyoType Puyo::GetPuyoID()
{
	return type_;
}

void Puyo::SoftDrop(void)
{
	dropSpeed_ = softdrop_;
}

void Puyo::SetAlive(bool alive)
{
	alive_ = alive;
}

bool Puyo::GetAlive(void)
{
	return alive_;
}

Vector2 Puyo::GetPos(void)
{
	return pos_;
}

Vector2 Puyo::SetPos(Vector2 pos)
{
	pos_ = pos;
	return pos_;
}

void Puyo::Init()
{
	dirPermit_ = { 1,1,1,1 };
	dropSpeed_ = 60;
	softdrop_ = 30;
	puyoFrame_ = 0;
}

void Puyo::Draw()
{
	DrawCircle(pos_.x + size_ / 2,pos_.y + size_ / 2,size_ / 2,0xffffff,true);
}
