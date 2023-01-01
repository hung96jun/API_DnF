#pragma once

struct Vector2;
class Actor;

struct TextureInfo
{
private:
	const int INDEX = 0;

public:
	TextureInfo() = default;
	TextureInfo(WSTR Key, WSTR Path, int MaxIndex, Vector2 TextureSize, Vector2 PrintSize, Vector2 Index, Vector2 Offset, COLORREF Alpha, Actor* Owner = nullptr);
	~TextureInfo();

	/**
	* @param	false is rendering consdition
	*/
	void SetHidden(bool Value) { bHidden = Value; }
	void SetLocation(const Vector2 Location)
	{
		this->Location = Location + (Offset * 0.5f);
	}
	const Actor* GetOwner() const { return Owner; }

	const Vector2 GetLocation() const { return Location; }
	const Vector2 GetOffset() const { return Offset; }
	const Vector2 GetPrintSize() const { return PrintSize; }
	const Vector2 GetTextureSize() const { return TextureSize; }
	const bool IsHidden() const { return bHidden; }
	const WSTR GetName() const { return Name; }
	const int GetIndex() const { return INDEX; }

	HBITMAP GetTexture() { return hTexture; }
	COLORREF GetAlpha() { return Alpha; }

	TextureInfo& operator=(const TextureInfo& Other)
	{
		this->Name = Other.Name;
		this->hTexture = Other.hTexture;
		this->Location = Other.Location;
		this->PrintSize = Other.PrintSize;
		this->TextureSize = Other.TextureSize;
		this->Alpha = Other.Alpha;
		this->Owner = Other.Owner;
		this->bHidden = Other.bHidden;

		return *this;
	}

private:
	WSTR Name = L"";
	HBITMAP hTexture = nullptr;
	Vector2 Offset = {};
	Vector2 Location = {};
	Vector2 PrintSize = {};
	Vector2 TextureSize = {};
	COLORREF Alpha = {};
	Actor* Owner = nullptr;

	bool bHidden = false;
};