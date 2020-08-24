#pragma once
#include <list>
#include <mutex>
#include <map>
#include <vector>
#include "common/Vector2.h"

#define lpEff Effect::GetInstance()

class Effect
{
public:
	static Effect& GetInstance()
	{
		static std::once_flag once;
		std::call_once(once, Create);
		return (*s_instance);
	}
	static void Create()
	{
		if (s_instance == nullptr)
		{
			s_instance = new Effect();
		}
	}
	static void Destroy()
	{
		delete s_instance;
		s_instance = nullptr;
	}
	void Draw();
	void Update();
	std::list <std::pair<std::string, Vector2>> playList_;
private:
	Effect();
	~Effect();
	bool Init();
	Vector2 pos;
	std::map<std::string,int> effectList_;				// エフェクトを管理するリスト
	std::vector<int> playingList_;
	static Effect* s_instance;
};

