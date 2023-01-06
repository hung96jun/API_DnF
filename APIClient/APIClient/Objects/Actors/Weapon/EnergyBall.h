#pragma once

<<<<<<< HEAD
class EnergyBall : public Weapon
{
private:
	const float THROW_RANGE = 100.0f;
	const float SPEED = 1200.0f;

	enum State
	{
		None,
		Fall,
		Boom,
	};

public:
	EnergyBall() = default;
	EnergyBall(Character* Owner);
=======
class EnergyBall : public Actor
{
private:
	const float THROW_RANGE = 100.0f;
	const float SPEED = 300.0f;

public:
	EnergyBall();
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
	~EnergyBall();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

<<<<<<< HEAD
	void SetLocation(const Vector2& Location);

	/**
	* Shoot Mode
	*/
	void OnShoot(const Vector2 Target);
	/**
	* Down Mode
	*/
	void OnShoot(const float& Height);

	virtual void OnBegin(RectCollision* Other) override;

	void SetDamage(const float& DamageMagnification);

private:
	void AnimationSetting();
	void ChangeBoom();
	void End();

	void OnMove() { bMove = true; }

	virtual void CollisionSetting() override;
=======
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
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c

private:
	Animation* Anim = nullptr;

	Vector2 Direction = {};
	Vector2 OriginLocation = {};
<<<<<<< HEAD

	Vector2	LandPoint = {};

	State CurState = None;

	bool bMove = false;

	float Start = 0.0f;
	float Cur = 0.0f;

	DamageHandle* hDamage = nullptr;
	float Damage = 0.0f;
=======
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
};
