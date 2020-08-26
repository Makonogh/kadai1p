#include "Puyo.h"
#include "DxLib.h"
#include "../_debug/_DebugConOut.h"

Puyo::Puyo() :size_(48)
{
}

Puyo::Puyo(Vector2 pos, PuyoType type):size_(48)
{
	pos_.y = pos.y;
	pos_.x = pos.x;
	type_ = type;
	
	Init();
}

Puyo::~Puyo()
{
}

bool Puyo::Update()
{
	if (dirPermit_.perBit.d == 1)
	{
		if (puyoFrame_ < dropSpeed_ )
		{
			puyoFrame_++;
		}	
		else
		{
			pos_.y+= dropLen_;
			puyoFrame_ = 0;
		}
		return false;
	}
	else
	{
		return true;
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

DirPermit Puyo::GetDirPermit()
{
	return dirPermit_;
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
	puyoFrame_ = dropSpeed_;
}

void Puyo::SetAlive(bool alive)
{
	alive_ = alive;
}

bool Puyo::GetAlive(void)
{
	if (alive_)
	{
		return true;
	}
	else
	{
		if (dethCount_ >= 20)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void Puyo::DethCount(void)
{
	if (!alive_)
	{
		dethCount_++;
	}
	else
	{
		dethCount_ = 0;
	};
}

void Puyo::ChangeSpeed(int t)
{
	dropLen_ = t;
	dropSpeed_ = 0;
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

int Puyo::GetColor_(PuyoType type)
{
	return color_[type];
}

void Puyo::Init()
{
	dirPermit_ = { 1,1,1,1 };
	dropSpeed_ = 5;
	softdrop_ = 5;
	puyoFrame_ = 0;
	dropLen_ = 4;
	dethCount_ = 0;
	alive_ = true;

	PuyoImage = LoadGraph("image/puyo.png",true);

	color_.try_emplace(PuyoType::RED, 0);
	color_.try_emplace(PuyoType::GREEN, 1);
	color_.try_emplace(PuyoType::YELLOW, 2);
	color_.try_emplace(PuyoType::BLUE, 3);
	color_.try_emplace(PuyoType::PURPLE, 4);
}

void Puyo::Draw()
{
	/*DrawCircle(pos_.x + size_ / 2,pos_.y + size_ / 2,size_ / 2,color_[type_],true);*/
	if (dethCount_ % 3 == 0)
	{
		DrawRectGraph(pos_.x, pos_.y, size_ * color_[type_], 0, size_, size_, PuyoImage, true, false);
	}
}
