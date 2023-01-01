#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	void Add(const int& Key, const TextureInfo& Texture);

	void PlayAnimation(const int& Key, bool Reverse = false);
	void Render(HDC hdc);

private:
	void CreateTextuer(const TextureInfo& Texture);

private:
	HDC hMemDC = nullptr;
	HBITMAP hTextureMap = nullptr;

	//vector<TextureInfo> Textures;
	std::map<int, std::vector<TextureInfo*>> Textures;
	std::vector<TextureInfo*> ViewTexturs;

	int ViewIndex = 0;
};
