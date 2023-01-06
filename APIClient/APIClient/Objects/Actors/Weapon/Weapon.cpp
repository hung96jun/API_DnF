#include "Framework/Framework.h"

#include "Weapon.h"
#include "Utilities/Implement.h"
#include "Objects/Actors/Characters/Monster/DogHead.h"

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

	Collision->SetActive(false);
	Collision->AddFunction(Implement<Weapon>(this, &Weapon::OnBegin));

	hDamage = new DamageHandle(this);

	//Collision->AddFunction(&Weapon::OnBegin);

	//std::function<void(Weapon*)> f = &Weapon::Function;
	//Collision->SetOwner(this);
	//Collision->AddFunction(Weapon::OnBegin);
	
}

Weapon::~Weapon()
{
	delete hDamage;
}

void Weapon::SetDamage(float DamageMultiplier)
{
	CurDamage = Owner->GetCurStatus().GetAttack();
	CurDamage *= DamageMultiplier;
}

void Weapon::OnBegin(RectCollision* Other)
{
	if (Other->GetOwner() == Owner) return;

	DogHead* test = static_cast<DogHead*>(Other->GetOwner());
	if (test == nullptr) return;

	Character* target = static_cast<Character*>(Other->GetOwner());
	if (target == nullptr) return;
	
	//test->Health -= CurDamage;
	hDamage->GiveDamage(target, CurDamage);
}

void Weapon::CollisionSetting()
{
}

void Weapon::Update()
{
	Super::Update();
}

void Weapon::Render(HDC hdc)
{
	Super::Render(hdc);
}

void Weapon::OnCollision(const Vector2& Offset, const Vector2& Size)
{
	this->Location = Owner->GetLocation() + Offset;
	Collision->SetSize(Size);
	Collision->SetActive(true);
	Collision->SetHidden(false);
}

void Weapon::EndCollision()
{
	Collision->SetActive(false);
	Collision->SetHidden(true);
	Collision->EndCollisionOverlap();
}

