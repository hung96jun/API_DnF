#include "Framework/Framework.h"
#include "CharacterStatus.h"

CharacterStatus::CharacterStatus(const float& Health, const float& Attack, const float& Defence, const float& Mana)
	:Health(Health), Attack(Attack), Defence(Defence), Mana(Mana)
{

}

const bool CharacterStatus::GiveDamage(const float& Damage)
{
	float damage = Damage;
	damage -= Defence;
	Health -= damage;

	if (Health <= 0.0f)
		return true;

	return false;
}
