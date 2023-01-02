#include "Framework/Framework.h"

#include "Actor.h"

Actor::Actor()
{
	Init();
}

Actor::Actor(Vector2 Location)
	: Location(Location)
{
	Init();
}

void Actor::Init()
{
	ObjectManager::Get()->Add(this);
	//CollisionManager::Get()->CreateCollision(Collision, CollisionChannel::Channel0);
	CREATE_COLLISION(Collision, CollisionChannel::Channel0);
	Collision->SetOwner(this);
	//Collision = new RectCollision(Vector2(0, 0), Vector2(81, 101));
	//Collision->SetActive(false);
}

Actor::~Actor()
{
	//delete Collision;
}

void Actor::Update()
{
	Collision->Update();
}

void Actor::Render(HDC hdc)
{
	Collision->Render(hdc);
}

