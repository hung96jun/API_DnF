#include "Framework/Framework.h"
#include "Block.h"

Block::Block()
	: Actor()
{
	Location = { WIN_CENTER_X, 20 };
	Collision->SetSize(Vector2(50, 50));
}

Block::~Block()
{
}

void Block::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Block::Init()
{
	Collision->AddFunction(Implement<Block>(this , &Block::OnBegin));
}

void Block::OnBegin(RectCollision* Other)
{
	if (Other == nullptr) return;

	hdc = GetDC(hWnd);

	if (hdc == nullptr) return;

	wstring str = L"Player OnBegin";
	TextOut(hdc, (int)(WIN_CENTER_X), (int)40, str.c_str(), (int)(str.length()));
}
