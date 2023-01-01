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
	}
	CutInfo(const Vector2& Start, const Vector2& End, const LoopType::Type& Loop = LoopType::Stop, const float& Speed = 0.1f)
		: Start(Start), End(End), Loop(Loop), Speed(Speed) {}

	Vector2 Start;
	Vector2 End;
	LoopType::Type Loop;
	float Speed = 0.1f;

	std::map<int, std::function<void()>> FrameFunction;
	std::function<void()> EndFunction;
};

struct SpriteInfo
{
public:
	SpriteInfo() = default;
	//SpriteInfo(SpriteInfo Other);
	SpriteInfo(const std::wstring& Path, const Vector2& Size, const Vector2& Index, const Vector2& Offset = Vector2(0, 0), COLORREF Alpha = MAGENTA);

	HBITMAP GetTexture() { return hTexture; }

	const Vector2 GetMaxIndex() { return MaxIndex; }
	const std::wstring GetPath() const { return Path; }
	const Vector2 GetLocation() const { return Location; }
	const Vector2 GetCutsize() const { return CutSize; }
	const Vector2 GetOffset() const { return Offset; }
	const Vector2 GetOriginSize() const { return OriginSize; }
	const CutInfo GetCutInfo(const int& Key) { return CutInfos[Key]; }
	void CallFrameFunction(const int& Key, const int& Frame)
	{
		if (CutInfos[Key].FrameFunction.count(Frame) == 0) return;
		CutInfos[Key].FrameFunction[Frame]();
	}

	void SetLocation(const Vector2& Value);
	void SetHidden(const bool& Value) { bHidden = Value; }
	void SetCutFrame(const int& Key, const Vector2& Start, const Vector2& End, const LoopType::Type& Loop = LoopType::Stop, const float& Speed = 1.0f);
	void SetEndFunction(const int& Key, std::function<void()> Func)
	{
		if (CutInfos[Key].EndFunction != nullptr) return;
		CutInfos[Key].EndFunction = Func;
	}
	void SetFrameFunction(const int& key, const int& Frame, std::function<void()> Func)
	{
		if (CutInfos[key].FrameFunction.count(Frame) > 0) return;
		CutInfos[key].FrameFunction[Frame] = Func;
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

	HBITMAP hTexture;
	Vector2 Location = {};
	Vector2 CutSize = {};
	Vector2 Offset = {};
	Vector2 OriginSize = {};
	Vector2 MaxIndex = {};
	COLORREF Alpha = MAGENTA;
	
	bool bHidden = false;

	std::map<int, CutInfo> CutInfos;
}; 