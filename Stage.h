#pragma once
#include "common/Vector2.h"
#include "input/Controller.h"
#include "Puyo/Puyo.h"
#include "NextMng.h"

#include <memory>
#include <vector>
#include <functional>
#include <list>

#define STAGE_CHIP_X 8
#define STAGE_CHIP_Y 14

class PlayUnit;
struct Drop;
struct Erase;
struct Fall;
struct Munyon;
struct Puyon;

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
	std::pair<int,Vector2> GetNextScreen();
	const Vector2& GetOffset(void);
	void Draw(void);
	void Update(void);
	Vector2 GetWorPos(Vector2 pos);						// ���[���h���W�̎擾
private:
	bool Init(void);									// �������֐�
	bool PuyoInstance();								// �Ղ�̐���
	bool OjamaInstance(std::shared_ptr<Puyo>& puyo);	// ������܂Ղ�̐���
	bool SetPermition(std::shared_ptr<Puyo>& puyo);	 	// �Ղ�̃p�[�~�b�V�����ݒ�
	void SetGamePad();									// �Q�[���p�b�h�̐ݒ�
	void SetKeyInput();									// �L�[�{�[�h�̐ݒ�
	Vector2 GetGrid(Vector2 pos);						// ���W����O���b�h���߂�֐�

	std::vector<std::shared_ptr<Puyo>> puyoVec_;		// �Ղ�̏����i�[

	std::unique_ptr<Controller> controller_;			// �R���g���[���[�����i�[���郆�j�[�N�|�C���^
	std::unique_ptr<PlayUnit> playUnit_;				// �v���C���[�����̂̏����i�[���郆�j�[�N�|�C���^
	
	std::vector<std::shared_ptr<Puyo>> baseData_;		// �Ղ�̔z�u�����i�[����ϐ� (�c�~��)	
	std::vector<std::shared_ptr<Puyo>*> data_;			// �Ղ�̔z�u���̈ꎟ�ϐ�(��)

	std::vector<std::shared_ptr<Puyo>> eraseBaseData_;	// �Ղ�̔z�u�����i�[����ϐ� (�c�~��)	
	std::vector<std::shared_ptr<Puyo>*> eraseData_;		// �Ղ�̔z�u���̈ꎟ�ϐ�(��)
	std::list<std::shared_ptr<Puyo>> ojamaList_;		// ������܂Ղ�̊i�[

	std::unique_ptr<NextMng> NextList_;					// NextMng�̊i�[

	Vector2 fieldPos_;								// �v���C�t�B�[���h�̍��W�i�Q��ʕ����Ȃ�PP�́i�O�C�O�j�݂����ȁj
	Vector2 fieldSize_;								// �v���C�t�B�[���h�̃T�C�Y
	Vector2 pos_;									// �X�e�[�W�̃I�t�Z�b�g(���[���h���W)
	Vector2 size_;									// �X�e�[�W�̃T�C�Y	
	Vector2 ojamaSize_;								// OjamaSize
	int screenID_;									// �`���̃X�N���[���̃o���h��
	int stageID_;									// �X�e�[�WID
	int ojamaID_;									// Ojama��ID
	static int stageCount_;							// �X�e�[�W�̐�����(�I�u�W�F�N�g�ł͂Ȃ��N���X���̂�)
	int id_;										// ID
	int blockSize_;									// 1�u���b�N�̃T�C�Y
	StageMode stagemode_;							// �X�e�[�W���[�h���i�[����ϐ�
	std::map<StageMode, std::function<void(Stage&)>> stageAct_;

	friend PlayUnit;
	friend Drop;
	friend Erase;
	friend Munyon;
	friend Puyon;
	friend Fall;
};		

