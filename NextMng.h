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
	Vector2Dbl size_;									// NEXT����޳�̃T�C�Y
	int id_;											// �ǂ̃v���C���[�̃l�N�X�g���c�����邽��
	int blockSize_;										// 1�}�X�T�C�Y
	int nextMax_;										// NEXT�i�[��
	int screenID_;										// �`��̃X�N���[��ID
	unsigned int count;									// ����ڂ̐������ۑ����邽�߁i����͂PP�ƂQP�œ����Ղ���o�����߂ɕK�v�j
	std::vector<std::shared_ptr<Puyo>> puyoList_;		// �Ղ�̎�ނ��i�[����ID
};

