#include "Framework/Framework.h"
#include "SpriteInfo.h"

//SpriteInfo::SpriteInfo(SpriteInfo Other)
//	:MAX_INDEX(Other.MAX_INDEX)
//{
//	this->Path = Other.Path;
//	this->hTexture = Other.hTexture;
//	this->Location = Other.Location;
//	this->CutSize = Other.CutSize;
//	this->Offset = Other.Offset;
//	this->OriginSize = Other.OriginSize;
//	this->Alpha = Other.Alpha;
//	this->Speed = Other.Speed;
//	this->bHidden = Other.bHidden;
//}

/**
* MaxSize로 스프라이트 이미지의 가로 세로 최대 갯수
* MaxIndex로 스프라이트 이미지의 총 갯수
* 두개를 따로 받아와야 할것같다.
*/
SpriteInfo::SpriteInfo(const std::wstring& Path, const Vector2& Size, const Vector2& Index, const Vector2& Offset, COLORREF Alpha)
	:Path(Path), MaxIndex(Index), Offset(Offset), OriginSize(Size), Alpha(Alpha)
{
	hTexture = (HBITMAP)LoadImage(hInst, Path.c_str(), IMAGE_BITMAP, Size.x, Size.y, LR_LOADFROMFILE);

	CutSize.x = Size.x / Index.x;
	CutSize.y = Size.y / Index.y;

	this->Offset.x -= (CutSize.x * 0.5f);
	this->Offset.x += Offset.x;
	this->Offset.y -= (CutSize.y * 0.5f);
	this->Offset.y += Offset.y;
}

void SpriteInfo::SetLocation(const Vector2& Value)
{
	Location = Value;
	Location += Offset;
}

void SpriteInfo::SetCutFrame(const int& Key, const Vector2& Start, const Vector2& End, const LoopType::Type& Loop, const float& Speed)
{
	CutInfos[Key] = CutInfo(Start, End, Loop, Speed);
}

