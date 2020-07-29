#pragma once
#include <array>
#include "Controller.h"
struct GamePad:
	public Controller
{
    ContType GetType(void) override;
    bool Setup(int no) override;
    bool Update(void) override;
private:
    std::map<InputID, int> _inputTbl;
    int _padInput;                      // パッドの入力情報
    int _connection;                    // 接続数の保存変数 
    int _id;                            // 接続パッドのID保存
};

