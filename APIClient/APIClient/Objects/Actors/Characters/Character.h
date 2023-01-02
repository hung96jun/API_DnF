#pragma once

class Animation;

class Character : public Actor
{
protected:
	enum Direction
	{
		Left,
		Right,
	};

private:
	const float GRAVITY = 980.0f;
	const float JUMP_POWER = 300.0f;

public:
	Character();
	Character(Vector2 Location);
	virtual ~Character() override;

	virtual void Update();
	virtual void Render(HDC hdc);

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	virtual void Init() override;

	virtual void AnimationSetting() = 0;
	virtual void AnimStateSetting() = 0;
	virtual void AnimationPlay() = 0;

protected:
	float Speed = 200.0f;
	Animation* Anim = nullptr;
};
