#include "Framework/Framework.h"

#include "Weapon.h"
#include "Utilities/Implement.h"

Weapon::Weapon(Character* Owner) 
	: Owner(Owner)
{
	Collision->SetCollisionChannel(CollisionChannel::Channel3);
	//Collision->AddFunction(&Weapon::Function);
	//Collision->AddFunction<Weapon>(&Weapon::Function);
	//std::function<void(Weapon&, Actor*)> function;
	//function = &Weapon::Function;
	//Collision->AddFunction(this, function);

	//Collision->AddFunction<Weapon>(this, &Weapon::OnBegin);

	Collision->AddFunction(Implement<Weapon>(this, &Weapon::OnBegin));

	//Collision->AddFunction(&Weapon::OnBegin);

	//std::function<void(Weapon*)> f = &Weapon::Function;
	//Collision->SetOwner(this);
	//Collision->AddFunction(Weapon::OnBegin);
	
}

Weapon::~Weapon()
{
}

void Weapon::OnBegin(RectCollision* Other)
{
	
}

void Weapon::Update()
{
}

void Weapon::Render(HDC hdc)
{
}

