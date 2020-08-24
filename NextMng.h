#pragma once
#include "Puyo/Puyo.h"

class NextMng
{
public:
	NextMng(Vector2 pos,Vector2 size);
	~NextMng();
	int GetScreenID();
	Vector2 GetPos();
private:
	void Init(Vector2 pos, Vector2 size);
	void Draw();
	Vector2 pos_;			// POS
	Vector2 size_;			// NEXT≥®›ƒﬁ≥ÇÃÉTÉCÉY
	int nextMax_;			// NEXTäiî[êî
	int screenID_;
};

