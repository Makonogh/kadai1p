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
	DROP,
	RENSA,
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
	bool Init(void);								// 初期化関数
	void EraseSet();								// ぷよの削除セット
	bool PuyoInstance();							// ぷよの生成
	bool ErasePuyo();								// ぷよの削除関数
	bool SetPermition(std::unique_ptr<Puyo>& puyo);			    	// ぷよのパーミッション設定

	std::vector<std::unique_ptr<Puyo>> puyoVec_;	// ぷよの情報を格納

	std::unique_ptr<Controller> controller_;		// コントローラー情報を格納するユニークポインタ
	std::unique_ptr<PlayUnit> playUnit_;			// プレイヤー処理のの情報を格納するユニークポインタ
	
	std::vector<PuyoType> baseData_;				// ぷよの配置情報を格納する変数 (縦×横)	
	std::vector<PuyoType*> data_;					// ぷよの配置情報の一次変数(横)

	std::vector<PuyoType> eraseBaseData_;			// ぷよの配置情報を格納する変数 (縦×横)	
	std::vector<PuyoType*> eraseData_;				// ぷよの配置情報の一次変数(横)

	Vector2 offset_;								// ステージのオフセット
	Vector2 size_;									// ステージのサイズ	
	int screenID_;									// 描画先のスクリーンのバンドル
	static int stageCount_;							// ステージの生成回数(オブジェクトではなくクラス自体の)
	int id_;										// ID
	int blockSize_;									// 1ブロックのサイズ
	StageMode stagemode_;							// ステージモードを格納する変数

	friend PlayUnit;
	friend Drop;
	friend Erase;
	friend Munyon;
	friend Puyo;
	friend Fall;
};		

