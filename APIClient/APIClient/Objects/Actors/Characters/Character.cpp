#include "Framework/Framework.h"

#include "Character.h"

Character::Character()
{
	Init();
}

Character::Character(Vector2 Location)
	: Actor(Location)
{
	Init();
}

Character::~Character()
{
}

void Character::Init()
{
	//Collision->SetCollisionChannel(CollisionChannel::Channel1);
	Collision->SetOwner(this);
	//Collision->AddFunction(&Character::OnBegin);
}

void Character::Update()
{
	Super::Update();

}

void Character::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Character::OnBegin(RectCollision* Other)
{
}
