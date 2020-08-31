#pragma once
#include "../common/Vector2.h"
#include "../input/Controller.h"

enum class PuyoType
{
	RED,
	GREEN,
	YELLOW,
	BLUE,
	PURPLE,
	OJAMA,
	WALL,
	NON,
	MAX
};

struct DirBit
{
	unsigned int u : 1;		// ��
	unsigned int d : 1;		// ��
	unsigned int l : 1;		// ��
	unsigned int r : 1;		// �E
};
// �ޯ�̨����
union DirPermit
{
	DirBit perBit;					// perBit�ɃA�N�Z�X
	unsigned int per;				// perBit�S�����A�N�Z�X����
};

// ���p��
class Puyo
{
public:
	Puyo();
	Puyo(Vector2 pos,PuyoType type);
	~Puyo();
	bool Update();	
	bool PuyonUpdate(Vector2 pos);
	void Move(InputID id);					// Move�֐�
	void Draw();							// �Ղ�̕`��֐�
	void SetDirPermit(DirPermit DirPermit); // �Ղ���ޯ�̨���ނ��i�[����֐�
	DirPermit GetDirPermit();				// perBit�̃Q�b�g�֐�
	const Vector2 GetGrid(int size);		// �Ղ�̃}�X�ڏ��
	PuyoType GetPuyoID();					// �Ղ��ID���Q�b�g����
	void SoftDrop(void);					// �\�t�g�h���b�v�֐�
	void SetAlive(bool alive);				// ���̐鍐(�����Ă������t���O)
	bool GetAlive(void);					// �t���O�̎擾
	void DethCount(void);					// ���̐鍐�̃J�E���g����֐�
	void SetLead(int x);					// ����Ղ�̃Z�b�g
	void SetSpos(int y);					// �X�e���X�Ղ�̍��W�Z�b�g
	void SetPuyon(bool puyon);				// �Ղ��ɐݒ�
	void SetGround(bool flag);
	bool GetGround();
	void ChangeSpeed(int t);				// �X�s�[�h�ύX�p�̊֐�
	Vector2 GetPos(void);					// �Ղ�̍��W�̎擾
	Vector2 SetPos(Vector2 pos);			// �Ղ�̍��W�̃Z�b�g
	int GetColor_(PuyoType type);			// �J���[�̎擾
private:
	void Init();							// �Ղ�̏�������
	std::map<PuyoType,int> color_;			// �Ղ�̃^�C�v�ƃJ���[
	DirPermit dirPermit_;					// �㉺���E���ޯ�̨����
	const int size_;						// ����
	Vector2 pos_;							// ���W
	int spos_y;								// �X�e���X�Ղ��Y���W(�\���������W)
	int PuyoImage;							// �Ղ�̉摜�i�[�ϐ�
	int dropSpeed_;							// �����鑬�x
	int dropLen_;							// �h���b�v�̗����镝
	int softdrop_;							// �\�t�g�h���b�v
	bool alive_;							// ���̐鍐
	bool fall_;
	bool puyon_;							// �Ղ��
	bool groZero_;					    	// �Ղ��̔��S�n
	int lead_;								// ���[�h�i����Ώ�1,�t���Ղ�2,���̂ق�(���łɒ��n�ς݂Ȃ�)0,�ɂȂ�ϐ��j�j
	PuyoType type_;							// �Ղ�̃^�C�v�i�[
	int puyoFrame_;							// �Ղ�̃t���[���J�E���g
	int puyonFrame_;						// �Ղ��̃J�E���g
	int dethCount_;							// �Ղ�̎��̐鍐�H�������̃J�E���g
	int puyoCount_;							// �Ղ�Ǝ��̃J�E���g�i��������Ă���������܂ŃJ�E���g��������i�A�j���[�V�����Ɏg���邩�ȂƁj�j
};

