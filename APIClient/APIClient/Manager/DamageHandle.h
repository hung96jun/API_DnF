#pragma once

class Character;
class Weapon;

class DamageHandle
{
public:
	DamageHandle() = default;
	DamageHandle(Weapon* Owner);
	~DamageHandle();

	const bool GiveDamage(Character* Target, const float& Damage);

private:
	Weapon* Owner = nullptr;
};