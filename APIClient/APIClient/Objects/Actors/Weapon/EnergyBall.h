#pragma once

class EnergyBall : public Actor
{
private:
	const float THROW_RANGE = 100.0f;
	const float SPEED = 300.0f;

public:
	EnergyBall();
	~EnergyBall();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	/**
	* Shot Mode
	*/
	void Play(Vector2 Target);
	/**
	* Down Mode
	*/
	void Play();

	virtual void OnBegin(RectCollision* Other) override;

private:
	void AnimationSetting();

private:
	Animation* Anim = nullptr;

	Vector2 Direction = {};
	Vector2 OriginLocation = {};
};
