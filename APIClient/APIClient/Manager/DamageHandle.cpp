#include "Framework/Framework.h"
#include "DamageHandle.h"

DamageHandle::DamageHandle(Weapon* Owner)
	:Owner(Owner)
{
}

DamageHandle::~DamageHandle()
{
	Owner = nullptr;
}

const bool DamageHandle::GiveDamage(Character* Target, const float& Damage)
{
	if (Target == nullptr) return false;
	if (Target == Owner->GetOwner()) return false;

	bool check = Target->GetCurStatus().GiveDamage(Damage);

	if (check == true)
		Target->OnDeath();

	return check;
}
