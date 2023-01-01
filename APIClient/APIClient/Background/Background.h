#pragma once

class Background
{
public:
	Background();
	~Background();

	void Update();
	void Render(HDC hdc);

private:
	int ImageIndex = 0;
	HBITMAP* BackImage = nullptr;
};