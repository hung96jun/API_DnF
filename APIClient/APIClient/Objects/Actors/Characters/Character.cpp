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
	delete Anim;
}

void Character::Init()
{
	//Collision->SetCollisionChannel(CollisionChannel::Channel1);
	Collision->SetOwner(this);
	Anim = new Animation(this);
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
