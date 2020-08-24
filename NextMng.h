#pragma once
#include "Puyo/Puyo.h"
#include <vector>

using PairPuyo = std::pair<std::shared_ptr<Puyo>,std::shared_ptr<Puyo>>;

class NextMng
{
public:
	NextMng(Vector2 pos,int size,int id);
	~NextMng();
	int GetScreenID();
	Vector2 GetPos();
	PairPuyo TakePuyo();
	void UpDateList();
	void Draw();
private:
	void Init(Vector2 pos, int size,int id);
	Vector2 pos_;										// POS
	Vector2Dbl size_;									// NEXTｳｨﾝﾄﾞｳのサイズ
	int id_;											// どのプレイヤーのネクストか把握するため
	int blockSize_;										// 1マスサイズ
	int nextMax_;										// NEXT格納数
	int screenID_;										// 描画のスクリーンID
	std::vector<std::shared_ptr<Puyo>> puyoList_;		// ぷよの種類を格納するID
};

