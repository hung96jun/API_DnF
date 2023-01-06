#pragma once

class DogHeadAIController;

class DogHead : public Character
{
private:
	const float MOVE_SPEED = 200.0f;
	const float THROW_INTERVAL = 0.015f;

	enum ShootType
	{
		Fall,
		Throw,
	};

	enum State
	{
		Idle_R = 0,
		Move_R = 1,
		Hit_R = 2,
		Dash_R = 3,

		Spear_R = 4,
		Glave_R = 5,
		Hook_R = 6,

		SpearStand_R = 7,
		
		DownCharge_R = 8,
		DownEnd_R = 9,
		ThrowCharge_R = 10,
		ThrowEnd_R = 11,

		Domerta_R = 12,		// 3 consecutive charge skill
		Pendeta_R = 13,		// Jump and doiwn sting

		Canaria_R = 14,		// 100 stack Holding

		Groggy_R = 15,
		GroggyEnd_R = 16,
		Death_R = 17,

		Idle_L = 18,
		Move_L = 19,
		Hit_L = 20,
		Dash_L = 21,

		Spear_L = 22,
		Glave_L = 23,
		Hook_L = 24,

		SpearStand_L = 25,

		DownCharge_L = 26,
		DownEnd_L = 27,
		ThrowCharge_L = 28,
		ThrowEnd_L = 29,

		Domerta_L = 30,		// 3 consecutive charge skill
		Pendeta_L = 31,		// Jump and doiwn sting

		Canaria_L = 32,		// 100 stack Holding

		Groggy_L = 33,
		GroggyEnd_L = 34,
		Death_L = 35,
	};

public:
	DogHead();
	virtual ~DogHead() override;

	virtual void Update();
	virtual void Render(HDC hdc);

	void SetTarget(const Character* Target) { this->Target = Target; }

	virtual void OnDeath() override;

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	//virtual void AnimationSetting() override;
	//virtual void AnimStateSetting() override;

	virtual void Init() override;

	///////////////////////////////////////////////////////////////////////////
	// Animation Bind Function
	///////////////////////////////////////////////////////////////////////////
	void ChangeIdleState();
	void ChangeGroggyEndState();

	void SetTargetDirection();

	void DashMove();
	void EndDash();

	void HookMove();
	void EndHook();

	void SpearMove();
	void EndSpear();

	void GlaveMove();
	void EndGlave();
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Timer Bind Function
	///////////////////////////////////////////////////////////////////////////
	void OnGroggy();
	void OnThrowCharging();

	void OnFallCharging();
	///////////////////////////////////////////////////////////////////////////

	void OnFallingBall();
	void OnThrowBall();

	void SetState();

	virtual void CollisionSetting() override;
	virtual void AnimationSetting() override;
	virtual void AnimStateSetting() override;
	virtual void AnimationPlay() override;
	void AISetting();
	void TimerFunctionSetting();

public:
	int Health = 100.0f;

private:
	DogHeadAIController* Controller = nullptr;
	Weapon* CurWeapon = nullptr;

	Vector2 OriginLocation = {};

	const Character* Target = nullptr;
	EnergyBallPolling* EnergyBalls;

	float ShootInterval = 0.0f;

	Vector2 MoveDir = {};
	ShootType Type;
	int SaveState;

	bool bChangeState = false;

	// Character을(를) 통해 상속됨
	
};
