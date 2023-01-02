#pragma once

class Monster : public Character
{
protected:
	enum State
	{
		Idle_R,
		Idle_L,
		Move_R,
		Move_L,
		Attack_R,
		Attack_L,
		Smash_R,
		Smash_L,
		Hit_R,
		Hit_L,
		Death_R,
		Death_L,
	};

public:
	Monster();
	Monster(Vector2 Location);
	virtual ~Monster() override;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetTarget(Character* Target) { this->Target = Target; }
	virtual void FiniteStateMachine() = 0;

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	virtual void Init() override;

	virtual void AnimationSetting() override {}
	virtual void AnimStateSetting() override {}

	virtual void AnimationPlay() override {}

protected:
	bool IsChangeState = true;

	Character* Target = nullptr;
	Direction CurDir = Left;
};