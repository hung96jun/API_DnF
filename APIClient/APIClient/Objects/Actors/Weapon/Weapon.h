#pragma once

class Character;
class DogHead;

class Weapon : public Actor
{
public:
	Weapon() = default;
	Weapon(Character* Owner);
	~Weapon();

	void Function() {}

	virtual void Update() override;

	virtual void Render(HDC hdc) override;

	void OnCollision(const Vector2& Offset, const Vector2& Size);
	void EndCollision();

	const Character* GetOwner() const { return Owner; }

	void SetDamage(float DamageMultiplier);

protected:
	virtual void OnBegin(RectCollision* Other) override;
	
protected:
	Character* Owner = nullptr;

private:
	DamageHandle* hDamage = nullptr;

	float CurDamage = 0.0f;

	// Actor을(를) 통해 상속됨
	virtual void CollisionSetting() override;
};
