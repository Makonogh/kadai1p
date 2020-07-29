#pragma once
#include "Stage.h"
#include <map>

class PlayUnit
{
public:
	PlayUnit(Stage& stage);
	~PlayUnit();
	bool Update();
	bool Init();
	
private:
	Stage& stage_;
	void RotPuyo(Vector2 vec1, Vector2 vec2, bool Rotate);
	int targetID_;

	std::map < InputID, std::function < void(CntData)>> KeyAct;
};

