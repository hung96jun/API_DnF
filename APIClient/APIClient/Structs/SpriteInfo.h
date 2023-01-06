#pragma once

struct Vector2;
class Actor;

namespace LoopType
{
	enum Type
	{
		Loop,
		Delay,
		Stop,
	};
}

struct CutInfo
{
public:
	CutInfo()
	{
		Start = Vector2();
		End = Vector2();
		Loop = LoopType::Stop;
		DelayTime = 0.0f;
	}
	CutInfo(const Vector2& Start, const Vector2& End, const Vector2& OriginSize, const LoopType::Type& Loop = LoopType::Stop, const float& Speed = 0.1f);

	Vector2 Start;
	Vector2 End;
	LoopType::Type Loop;
	float Speed = 0.1f;
	int Frame = 0;
	
	float DelayTime;
	std::map<int, std::function<void()>> FrameFunction;
	std::function<void()> EndFunction;
	/**
	* @Key	KeyValue x is Start Frame, KeyValue y is End Frame
	*/
	//std::map<Vector2, std::function<void()>> RangeFunction;
};

struct SpriteInfo
{
public:
	SpriteInfo() = default;
	//SpriteInfo(SpriteInfo Other);
	SpriteInfo(const std::wstring& Path, const Vector2& Size, const Vector2& Index, const int& MaxCount, const Vector2& Offset = Vector2(0, 0), COLORREF Alpha = MAGENTA);

	HBITMAP GetTexture() { return hTexture; }

	const Vector2 GetMaxIndex() { return MaxIndex; }
	const std::wstring GetPath() const { return Path; }
	const Vector2 GetLocation() const { return Location; }
	const Vector2 GetCutsize() const { return CutSize; }
	const Vector2 GetOffset() const { return Offset; }
	const Vector2 GetOriginSize() const { return OriginSize; }
	const CutInfo GetCutInfo(const int& Key) { return CutInfos[Key]; }
	const COLORREF GetAlpha() { return Alpha; }
	void CallFrameFunction(const int& Key, const int& Frame)
	{
		if (CutInfos[Key].FrameFunction.count(Frame) == 0) return;
		CutInfos[Key].FrameFunction[Frame]();
	}
	//void CallRangeFrameFunction(const int& Key, const int& Frame)
	//{
	//	for (std::pair<Vector2, std::function<void()>> funcPair : CutInfos[Key].RangeFunction)
	//	{
	//		if (funcPair.first.x >= Frame)
	//		{
	//			if (funcPair.first.y <= Frame)
	//			{
	//				funcPair.second();
	//			}
	//		}
	//	}
	//}

	void SetLocation(const Vector2& Value);
	void SetHidden(const bool& Value) { bHidden = Value; }
	void SetCutFrame(const int& Key, const Vector2& Start, const Vector2& End, const LoopType::Type& Loop = LoopType::Stop, const float& Speed = 1.0f);
	void SetEndFunction(const int& Key, std::function<void()> Func)
	{
		if (CutInfos[Key].EndFunction != nullptr) return;
		CutInfos[Key].EndFunction = Func;
	}
	//void AddRangeFrameFunction(const int& Key, const int& Start, const int& End, std::function<void()> Func)
	//{
	//	Vector2 frame = { (float)Start, (float)End };
	//	CutInfos[Key].RangeFunction[frame] = Func;
	//}
	void SetFrameFunction(const int& key, const int& Frame, std::function<void()> Func)
	{
		if (CutInfos[key].FrameFunction.count(Frame) > 0) return;
		CutInfos[key].FrameFunction[Frame] = Func;
	}
	void SetDelayTime(const int& Key, const float& DelayTime)
	{
		if (CutInfos[Key].DelayTime != 0.0f) return;
		CutInfos[Key].DelayTime = DelayTime;
	}

	SpriteInfo& operator=(const SpriteInfo& Other)
	{
		this->Path = Other.Path;
		this->hTexture = Other.hTexture;
		this->Location = Other.Location;
		this->CutSize = Other.CutSize;
		this->Offset = Other.Offset;
		this->MaxIndex = Other.MaxIndex;
		this->OriginSize = Other.OriginSize;
		this->Alpha = Other.Alpha;
		this->bHidden = Other.bHidden;
		this->CutInfos = Other.CutInfos;

		return *this;
	}

private:
	std::wstring Path = L"";

	HBITMAP hTexture = nullptr;
	Vector2 Location = {};
	Vector2 CutSize = {};
	Vector2 Offset = {};
	Vector2 OriginSize = {};
	Vector2 MaxIndex = {};
	UINT MaxCount = 0;
	COLORREF Alpha = MAGENTA;

	bool bHidden = false;

	std::map<int, CutInfo> CutInfos;
};