#pragma once

class Character : public Actor
{
private:
	const float GRAVITY = 980.0f;
	const float JUMP_POWER = 300.0f;

public:
	Character();
	Character(Vector2 Location);
	~Character();

	virtual void Update();
	virtual void Render(HDC hdc);

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	virtual void Init() override;

protected:
	float Speed = 200.0f;
};
