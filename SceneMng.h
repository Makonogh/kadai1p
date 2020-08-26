#pragma once
#include <vector>
#include <memory>
#include <mutex>
#include "Stage.h"
#include <cassert>

#define lpSceneMng SceneMng::GetInstance()

class SceneMng
{
public:
	static SceneMng& GetInstance()
	{
		static std::once_flag once;
		std::call_once(once, Create);
		return *s_instance;
	}

	static void Create()
	{
		if (s_instance == nullptr)
		{
			s_instance = new SceneMng();
		}
	}

	static void Destroy()
	{
		delete s_instance;
		s_instance = nullptr;
	}
	void Run(void);
	const Vector2 screenSize_;
private:
	SceneMng();
	~SceneMng();
	void Draw(void);
	bool Init(void);

	std::vector<std::unique_ptr<Stage>> playStage_;
	
	int frame_;
	int backImage;									// ”wŒi‚Ì•`‰æ•Ï”
	static SceneMng *s_instance;
};

