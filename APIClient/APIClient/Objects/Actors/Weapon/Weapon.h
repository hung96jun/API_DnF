#pragma once

class Character;

class Weapon : public Actor
{
public:
	Weapon() = default;
	Weapon(Character* Owner);
	~Weapon();

	void Function() {}

	virtual void Update() override;

	virtual void Render(HDC hdc) override;

	void OnCollision(const Vector2& Location, const Vector2& Size);
	void EndCollision() { Collision->SetActive(false); }

protected:
	virtual void OnBegin(RectCollision* Other) override;
	
private:
	Character* Owner = nullptr;
};
