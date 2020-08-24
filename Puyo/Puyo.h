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
	unsigned int u : 1;		// 上
	unsigned int d : 1;		// 下
	unsigned int l : 1;		// 左
	unsigned int r : 1;		// 右
};
// ﾋﾞｯﾄﾌｨｰﾙﾄﾞ
union DirPermit
{
	DirBit perBit;					// perBitにアクセス
	unsigned int per;				// perBit全部をアクセスする
};

// 共用体
class Puyo
{
public:
	Puyo();
	Puyo(Vector2 pos,PuyoType type);
	~Puyo();
	bool Update();	
	void Move(InputID id);					// Move関数
	void Draw();							// ぷよの描画関数
	void SetDirPermit(DirPermit DirPermit); // ぷよのﾋﾞｯﾄﾌｨｰﾙﾄﾞを格納する関数
	DirPermit GetDirPermit();				// perBitのゲット関数
	const Vector2 GetGrid(int size);		// ぷよのマス目情報
	PuyoType GetPuyoID();					// ぷよのIDをゲットする
	void SoftDrop(void);					// ソフトドロップ関数
	void SetAlive(bool alive);				// 死の宣告(消していいかフラグ)
	bool GetAlive(void);					// フラグの取得
	void ChangeSpeed(int t);				// スピード変更用の関数
	Vector2 GetPos(void);					// ぷよの座標の取得
	Vector2 SetPos(Vector2 pos);			// ぷよの座標のセット
private:
	void Init();							// ぷよの初期化関数
	std::map<PuyoType,int> color_;			// ぷよのタイプとカラー
	DirPermit dirPermit_;					// 上下左右のﾋﾞｯﾄﾌｨｰﾙﾄﾞ
	const int size_;						// ｻｲｽﾞ
	Vector2 pos_;							// 座標
	int dropSpeed_;							// 落ちる速度
	int dropLen_;							// ドロップの落ちる幅
	int softdrop_;							// ソフトドロップ
	bool alive_;							// 死の宣告
	PuyoType type_;							// ぷよのタイプ格納
	int puyoFrame_;							// ぷよのフレームカウント
};

