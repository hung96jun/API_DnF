#include "Framework/Framework.h"
#include "TextureInfo.h"
#include "Objects/Actors/Actor.h"


TextureInfo::TextureInfo(WSTR Key, WSTR Path, int MaxIndex, Vector2 TextureSize, Vector2 PrintSize, Vector2 Index, Vector2 Offset, COLORREF Alpha, Actor* Owner)
	: Name(Key), INDEX(MaxIndex), Offset(Offset), Alpha(Alpha), Owner(Owner), PrintSize(PrintSize), TextureSize(TextureSize)
{
	hTexture = (HBITMAP)LoadImage(hInst, Path, IMAGE_BITMAP,
		(int)TextureSize.x, (int)TextureSize.y, LR_LOADFROMFILE);
} 

TextureInfo::~TextureInfo()
{
	DeleteObject(hTexture);
}
