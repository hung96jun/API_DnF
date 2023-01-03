#pragma once

class Background
{
public:
	Background() = default;
	Background(std::wstring Path, Vector2 Size);
	~Background();

	BITMAP GetTexture() { return Texture; }

	void Update();
	void Render(HDC hdc);

private:
	//int ImageIndex = 0;
	HDC hMemDC = nullptr;
	BITMAP Texture;
	HBITMAP hBackMap = nullptr;

	RectCollision BackRect = {};
};