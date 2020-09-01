#include "Puyo.h"
#include "DxLib.h"
#include "../_debug/_DebugConOut.h"

Puyo::Puyo() :size_(48)
{
	pos_.y = 0;
	pos_.x = 0;
	type_ = PuyoType::RED;
	Init();
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
	puyoCount_++;

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
		if (!fall_)
		{
			dropLen_ = 4;
		}
		return false;
	}
	else
	{
		dropCount_++;
		return true;
	}
	return false;
}

bool Puyo::PuyonUpdate(Vector2 Gpos)
{
	puyonFrame_++;
	if (puyonFrame_ > 60)
	{
		puyon_ = false;
		groZero_ = false;
	}
	if (groZero_)
	{
		pos_.y -= puyonFrame_;
		return true;
	}
	if (puyon_)
	{
		return true;
	}
	else
	{
		puyonFrame_ = 0;
		return false;
	}
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
	dropLen_ = 12;
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

int Puyo::GetDropCount(void)
{
	return dropCount_;
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

void Puyo::SetLead(int x)
{
	lead_ = x;
}

void Puyo::SetSpos(int y)
{
	spos_y = y;
}

void Puyo::SetPuyon(bool puyon)
{
	puyon_ = puyon;
}

void Puyo::SetGround(bool flag)
{
	groZero_ = flag;
}

bool Puyo::GetGround()
{
	return groZero_;
}

void Puyo::ChangeSpeed(int t)
{
	dropLen_ = t;
	fall_ = true;
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
	puyon_ = false;
	groZero_ = false;
	fall_ = false;
	lead_ = 0;
	spos_y = 0;
	puyoCount_ = -1;
	puyonFrame_ = 0;
	PuyoImage = LoadGraph("image/puyo.png",true);
	dropCount_ = 0;

	color_.try_emplace(PuyoType::RED, 0xff0000);
	color_.try_emplace(PuyoType::GREEN, 0x00ff00);
	color_.try_emplace(PuyoType::YELLOW, 0xffff00);
	color_.try_emplace(PuyoType::BLUE, 0x0000ff);
	color_.try_emplace(PuyoType::PURPLE, 0xff00ff);
}

void Puyo::Draw()
{
	if (lead_ != 0)
	{
		DrawCircle(pos_.x + size_ / 2, (spos_y - 1) * size_ + size_ / 2, size_ / 5, color_[type_], true);
	}
	if (dethCount_ % 3 == 0)
	{
		DrawRectGraph(pos_.x, pos_.y, size_ * static_cast<int>(type_), 0, size_, size_, PuyoImage, true, false);
		if (lead_ == 1)
		{
			int alpha = 0;
			if ((puyoCount_ / 30) % 2 == 0)
			{
				alpha = (puyoCount_ % 30) * 2;
			}
			else
			{
				alpha = (30 - puyoCount_ % 30) * 2;
			}
			SetDrawBlendMode(DX_BLENDMODE_SUB, alpha);		//ブレンドモード
			DrawRectGraph(pos_.x, pos_.y, size_ * static_cast<int>(type_), 0, size_, size_, PuyoImage, true, false);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
		}
	}
}
