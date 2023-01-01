#include "Framework/Framework.h"
#include "Texture.h"

Texture::Texture()
{
	HDC hdc = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(hWnd, hdc);
}

Texture::~Texture()
{
	DeleteObject(hMemDC);
	DeleteObject(hTextureMap);
}

void Texture::CreateTextuer(const TextureInfo& Texture)
{
}

void Texture::Add(const int& Key, const TextureInfo& Texture)
{
	TextureInfo* info = new TextureInfo(Texture);
	vector<TextureInfo*> textures;

	hTextureMap = info->GetTexture();
	SelectObject(hMemDC, hTextureMap);

	// 입력된 Key값이 있을 경우
	if (Textures.count(Key) > 0)
	{
		textures = Textures[Key];
	}

	textures.push_back(info);
	Textures[Key] = textures;
}

void Texture::PlayAnimation(const int& Key, bool Reverse)
{
	if (Textures.count(Key) == false) return;

	// 정방향일때
	if (Reverse == false)
		ViewTexturs = Textures[Key];

	// 역방향일때
	else
	{
		const int max = (const int)Textures[Key].size();
		for (int i = 0; i < max; ++i)
		{
			ViewTexturs.push_back(Textures[Key][max - (i + 1)]);
		}
	}

	ViewIndex = 0;
}

void Texture::Render(HDC hdc)
{
	TextureInfo* info = ViewTexturs[ViewIndex];
	HBITMAP htexture = info->GetTexture();

	SelectObject(hMemDC, htexture);
	
	Vector2 pos = info->GetLocation();
	Vector2 size = info->GetPrintSize();
	Vector2 textureSize = info->GetTextureSize();
	Vector2 offset = info->GetOffset();

	GdiTransparentBlt(hdc,
		//pos.x, pos.y,
		(int)(pos.x - (size.x + (offset.x * 0.5f))), (int)(pos.y - (size.y - (offset.y * 0.5f))),
		(int)(pos.x + (size.x + (offset.x * 0.5f))), (int)(pos.y + (size.y + (offset.y * 0.5f))),
		hMemDC,
		0, 0,
		(int)textureSize.x, (int)textureSize.y,
		info->GetAlpha());

	if (ViewTexturs[ViewIndex]->GetIndex() > 0)
	{
		++ViewIndex;
		ViewIndex %= info->GetIndex();
	}
}
