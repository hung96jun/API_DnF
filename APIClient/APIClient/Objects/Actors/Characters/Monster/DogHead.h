#pragma once

class DogHead : public Character
{
private:
	const float MOVE_SPEED = 200.0f;

	enum State
	{
		Idle_R,
		Move_R,
		Hit_R,
		Dash_R,

		//_RSpearPose,
		Spear_R,
		Glave_R,
		Hook_R,

		SpearStand_R,
		
		DownCharge_R,
		ThrowCharge_R,
		ThrowEnd_R,

		Domerta_R,		// 3 consecutive charge skill
		Pendeta_R,		// Jump and doiwn sting

		Canaria_R,		// 100 stack Holding

		Groggy_R,
		GroggyEnd_R,
		Death_R,

		Idle_L,
		Move_L,
		Hit_L,
		Dash_L,

		//_LSpearPose,
		Spear_L,
		Glave_L,
		Hook_L,

		SpearStand_L,

		DownCharge_L,
		ThrowCharge_L,
		ThrowEnd_L,

		Domerta_L,		// 3 consecutive charge skill
		Pendeta_L,		// Jump and doiwn sting

		Canaria_L,		// 100 stack Holding

		Groggy_L,
		GroggyEnd_L,
		Death_L,
	};
public:
	DogHead();
	virtual ~DogHead() override;

	virtual void Update();
	virtual void Render(HDC hdc);

protected:
	virtual void OnBegin(RectCollision* Other) override;

private:
	//virtual void AnimationSetting() override;
	//virtual void AnimStateSetting() override;

	virtual void Init() override;

	virtual void AnimationSetting() override;
	virtual void AnimStateSetting() override;
	virtual void AnimationPlay() override;
	void TimerFunctionSetting();

	///////////////////////////////////////////////////////////////////////////
	// Animation Bind Function
	///////////////////////////////////////////////////////////////////////////
	void ChangeIdleState();
	void ChangeGroggyEndState();
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// Timer Bind Function
	///////////////////////////////////////////////////////////////////////////
	void OnGroggy();
	void OnThrowCharging();
	///////////////////////////////////////////////////////////////////////////

	void OnThrowBall();

private:
	Vector2 OriginLocation = {};


	std::function<void()> temp;
//private:
//	State BeforeState;
//	State CurState;
};
