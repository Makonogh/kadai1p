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
	void Move(InputID id);					// Move�֐�
	void Draw();							// �Ղ�̕`��֐�
	void SetDirPermit(DirPermit DirPermit); // �Ղ���ޯ�̨���ނ��i�[����֐�
	DirPermit GetDirPermit();				// perBit�̃Q�b�g�֐�
	const Vector2 GetGrid(int size);		// �Ղ�̃}�X�ڏ��
	PuyoType GetPuyoID();					// �Ղ��ID���Q�b�g����
	void SoftDrop(void);					// �\�t�g�h���b�v�֐�
	void SetAlive(bool alive);				// ���̐鍐(�����Ă������t���O)
	bool GetAlive(void);					// �t���O�̎擾
	void ChangeSpeed(int t);				// �X�s�[�h�ύX�p�̊֐�
	Vector2 GetPos(void);					// �Ղ�̍��W�̎擾
	Vector2 SetPos(Vector2 pos);			// �Ղ�̍��W�̃Z�b�g
	int GetColor_(PuyoType type);			// �J���[�̎擾
private:
	void Init();							// �Ղ�̏������֐�
	std::map<PuyoType,int> color_;			// �Ղ�̃^�C�v�ƃJ���[
	DirPermit dirPermit_;					// �㉺���E���ޯ�̨����
	const int size_;						// ����
	Vector2 pos_;							// ���W
	int dropSpeed_;							// �����鑬�x
	int dropLen_;							// �h���b�v�̗����镝
	int softdrop_;							// �\�t�g�h���b�v
	bool alive_;							// ���̐鍐
	PuyoType type_;							// �Ղ�̃^�C�v�i�[
	int puyoFrame_;							// �Ղ�̃t���[���J�E���g
};

