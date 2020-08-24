#include "Effect.h"
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "_debug/_DebugConOut.h"

Effect* Effect::s_instance = nullptr;

void Effect::Draw()
{
	for (auto data : playList_)
	{
		playingList_.emplace_back(PlayEffekseer2DEffect(effectList_[data.first]));
		SetPosPlayingEffekseer2DEffect(playingList_.back(), data.second.x, data.second.y, 0);
		SetSpeedPlayingEffekseer2DEffect(playingList_.back(), 5.0);
	}
	playList_.clear();
}

void Effect::Update()
{
	UpdateEffekseer2D();
	DrawEffekseer2D();
	for (auto data : playingList_)
	{
		playingList_.erase(std::remove_if(playingList_.begin(), playingList_.end(),
			[](int data) {
			return IsEffekseer2DEffectPlaying(data); })
			, playingList_.end());
	}
	//TRACE("%d", playingList_.size());
}

Effect::Effect()
{
	Init();
}

Effect::~Effect()
{
}

bool Effect::Init()
{
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (Effekseer_Init(8000) == -1)
	{
		return -1;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
	Effekseer_Set2DSetting(1280, 720);

	effectList_.emplace("”j‰ó",LoadEffekseerEffect("dissap.efk", 2.0f));

	SetUseZBuffer3D(TRUE);

	SetWriteZBuffer3D(TRUE);

	playingList_.clear();

	return true;
}


