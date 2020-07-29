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
    int _padInput;                      // �p�b�h�̓��͏��
    int _connection;                    // �ڑ����̕ۑ��ϐ� 
    int _id;                            // �ڑ��p�b�h��ID�ۑ�
};

