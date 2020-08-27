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
	Vector2 GetWorPos(Vector2 pos);						// ワールド座標の取得
private:
	bool Init(void);									// 初期化関数
	bool PuyoInstance();								// ぷよの生成
	bool OjamaInstance(std::shared_ptr<Puyo>& puyo);	// おじゃまぷよの生成
	bool SetPermition(std::shared_ptr<Puyo>& puyo);	 	// ぷよのパーミッション設定
	void GetSpuyo(void);			// ステルスぷよを探す関数
	void SetGamePad(void);								// ゲームパッドの設定
	void SetKeyInput(void);								// キーボードの設定
	Vector2 GetGrid(Vector2 pos);						// 座標からグリッド求める関数

	std::vector<std::shared_ptr<Puyo>> puyoVec_;		// ぷよの情報を格納

	std::unique_ptr<Controller> controller_;			// コントローラー情報を格納するユニークポインタ
	std::unique_ptr<PlayUnit> playUnit_;				// プレイヤー処理のの情報を格納するユニークポインタ
	
	std::vector<std::shared_ptr<Puyo>> baseData_;		// ぷよの配置情報を格納する変数 (縦×横)	
	std::vector<std::shared_ptr<Puyo>*> data_;			// ぷよの配置情報の一次変数(横)

	std::vector<std::shared_ptr<Puyo>> eraseBaseData_;	// ぷよの配置情報を格納する変数 (縦×横)	
	std::vector<std::shared_ptr<Puyo>*> eraseData_;		// ぷよの配置情報の一次変数(横)
	std::list<std::shared_ptr<Puyo>> ojamaList_;		// おじゃまぷよの格納

	std::unique_ptr<NextMng> NextList_;					// NextMngの格納

	Vector2 fieldPos_;								// プレイフィールドの座標（２画面分割なら１Pは（０，０）みたいな）
	Vector2 fieldSize_;								// プレイフィールドのサイズ
	Vector2 pos_;									// ステージのオフセット(ワールド座標)
	Vector2 size_;									// ステージのサイズ	
	Vector2 ojamaSize_;								// OjamaSize
	int screenID_;									// 描画先のスクリーンのバンドル
	int stageID_;									// ステージID
	int ojamaID_;									// OjamaのID
	static int stageCount_;							// ステージの生成回数(オブジェクトではなくクラス自体の)
	int id_;										// ID
	int blockSize_;									// 1ブロックのサイズ
	StageMode stagemode_;							// ステージモードを格納する変数
	std::map<StageMode, std::function<void(Stage&)>> stageAct_;

	

	friend PlayUnit;
	friend Drop;
	friend Erase;
	friend Munyon;
	friend Puyon;
	friend Fall;
};		

