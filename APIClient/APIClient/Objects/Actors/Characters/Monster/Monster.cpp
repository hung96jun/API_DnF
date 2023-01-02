#include "Framework/Framework.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(Vector2 Location)
{
}

Monster::~Monster()
{
	Target = nullptr;
}

void Monster::Update()
{
	FiniteStateMachine();
}

void Monster::Render(HDC hdc)
{
}

void Monster::OnBegin(RectCollision* Other)
{
}

void Monster::Init()
{
}
