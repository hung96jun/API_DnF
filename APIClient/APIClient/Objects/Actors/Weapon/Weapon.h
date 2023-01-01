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

protected:
	virtual void OnBegin(RectCollision* Other) override;
	
private:
	Character* Owner = nullptr;
};
