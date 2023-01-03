#include "Framework/Framework.h"
#include "Background.h"

Background::Background(std::wstring Path, Vector2 Size)
{
	HDC hdc = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hdc);
	hBackMap = (HBITMAP)LoadImage(hInst, Path.c_str(), IMAGE_BITMAP, Size.x, Size.y, LR_LOADFROMFILE);
	ReleaseDC(hWnd, hdc);

	SelectObject(hMemDC, hBackMap);
	GetObject(hBackMap, sizeof(BITMAP), &Texture);

	Camera::Get()->SetTexture(Texture);
	Camera::Get()->SetBackgroundRect(&BackRect);
}

Background::~Background()
{
}

void Background::Update()
{
}

void Background::Render(HDC hdc)
{
	bool check = BitBlt(
		hdc,
		0, 0,
		WIN_WIDTH, WIN_HEIGHT,
		hMemDC,
		BackRect.Left(), BackRect.Top(),
		SRCCOPY
	);

	if (check == true)
		int a = 10;

	else
		int a = 10;
}
