#pragma once
#include "common/Vector2.h"
#include "input/Controller.h"
#include "Puyo.h"
#include "StageMode/Drop.h"
#include "StageMode/Erase.h"
#include "StageMode/Munyon.h"
#include "StageMode/Puyon.h"
#include "StageMode/Fall.h"
#include <memory>
#include <vector>
#include <functional>

#define STAGE_CHIP_X 8
#define STAGE_CHIP_Y 14

class PlayUnit;

enum class StageMode
{
	Drop,
	Erase,
	Fall,
	Munyon,
	Puyon,
	MAX
};

class Stage
{
public:
	Stage(Vector2&& offset,Vector2&& size);
	~Stage();
	int GetStageDraw(void);
	const Vector2& GetOffset(void);
	void Draw(void);
	void Update(void);
private:
	bool Init(void);									// �������֐�
	void EraseSet();									// �Ղ�̍폜�Z�b�g
	bool PuyoInstance();								// �Ղ�̐���
	bool ErasePuyo();									// �Ղ�̍폜�֐�
	bool SetPermition(std::unique_ptr<Puyo>& puyo);	 	// �Ղ�̃p�[�~�b�V�����ݒ�

	std::vector<std::shared_ptr<Puyo>> puyoVec_;		// �Ղ�̏����i�[

	std::unique_ptr<Controller> controller_;			// �R���g���[���[�����i�[���郆�j�[�N�|�C���^
	std::unique_ptr<PlayUnit> playUnit_;				// �v���C���[�����̂̏����i�[���郆�j�[�N�|�C���^
	
	std::vector<std::shared_ptr<Puyo>> baseData_;		// �Ղ�̔z�u�����i�[����ϐ� (�c�~��)	
	std::vector<std::shared_ptr<Puyo>*> data_;			// �Ղ�̔z�u���̈ꎟ�ϐ�(��)

	std::vector<std::shared_ptr<Puyo>> eraseBaseData_;	// �Ղ�̔z�u�����i�[����ϐ� (�c�~��)	
	std::vector<std::shared_ptr<Puyo>*> eraseData_;		// �Ղ�̔z�u���̈ꎟ�ϐ�(��)

	Vector2 offset_;								// �X�e�[�W�̃I�t�Z�b�g
	Vector2 size_;									// �X�e�[�W�̃T�C�Y	
	int screenID_;									// �`���̃X�N���[���̃o���h��
	static int stageCount_;							// �X�e�[�W�̐�����(�I�u�W�F�N�g�ł͂Ȃ��N���X���̂�)
	int id_;										// ID
	int blockSize_;									// 1�u���b�N�̃T�C�Y
	StageMode stagemode_;							// �X�e�[�W���[�h���i�[����ϐ�
	std::map<StageMode, std::function<void(Stage&)>> stageAct_;

	friend PlayUnit;
	friend Drop;
	friend Erase;
	friend Munyon;
	friend Puyo;
	friend Fall;
};		

