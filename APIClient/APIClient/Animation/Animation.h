#pragma once
#include "Structs/SpriteInfo.h"

class Animation
{
public:
	Animation() = default;
	Animation(Actor* Owner);
	~Animation();

	//void Add(const int& Key, SpriteInfo Sprite);
	//void Add(const int& Key, SpriteInfo Sprite);
	/**
	* @param	FileName	FileName + extension
	*/
	void Add(const WSTR& FileName, SpriteInfo Sprite);
	void SetFrame(const WSTR& FileName, const int& Key, const Vector2& Start, const Vector2& End, const LoopType::Type& Loop = LoopType::Stop, const float& Speed = 0.0f);
	void AddFrameFunction(const WSTR& FileName, const int& Key, const int& Frame, std::function<void()> Func);
	void SetEndFunction(const WSTR& FileName, const int& Key, std::function<void()> Func);
	//void AddRangeFunction(const std::wstring& FileName, const int& Key, const int& Start, const int& End, std::function<void()> Func);
	void SetDelayTime(const WSTR& FileName, const int& Key, const float& DelayTime);
	void Remove(const WSTR& FileName);
	void Destroy();

	void Play(const int& Key);
	void ReversePlay(const int& Key);

	void Update();
	void Render(HDC hdc);
	void Render(HDC hdc, int Alpha);

	void ResetAnimation();

	HDC GetMemDC() { return hMemDC; }

private:
	void ResetFrame();

private:
	HDC hMemDC = nullptr;
	HDC hAlphaMemDC = nullptr;
	HBITMAP hBitMap = nullptr;
	//HBITMAP hBeforeMap = nullptr;
	HBITMAP hAlphaBitMap = nullptr;

	std::map<std::wstring, SpriteInfo*> Animations;
	std::map<int, std::wstring> KeySet;

	int CurIndex = 0;
	Vector2 CurFrame = {};
	int CountFrame = 0;
	float CurTime = 0.0f;

	SpriteInfo* CurAnim = nullptr;
	Actor* Owner = nullptr;
	//bool bLoop = false;
	LoopType::Type Loop = LoopType::Stop;
	bool bPlay = false;

	int SelectKey = 0;

	SpriteInfo* Info;

	float DelayTime = 0.0f;
};
