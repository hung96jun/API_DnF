#pragma once

struct CharacterStatus
{
public:
	CharacterStatus() = default;
	CharacterStatus(const float& Health, const float& Attack, const float& Defence, const float& Mana);

	const float GetHealth() const { return Health; }
	const float GetDefence() const { return Defence; }
	const float GetAttack() const { return Attack; }
	const float GetManage() const { return Mana; }
	const float GetDamage() const { return Defence; }
	/**
	* @return	Survival check
	*/
	const bool GiveDamage(const float& Damage);

private:
	float Health;
	float Attack;
	float Defence;
	float Mana;
};