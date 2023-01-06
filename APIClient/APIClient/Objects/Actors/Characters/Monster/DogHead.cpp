#include "Framework/Framework.h"
#include "DogHead.h"

#include "Objects/Actors/Weapon/Weapon.h"
#include "AI/DogHeadAIController.h"

DogHead::DogHead()
{
	Init();
}

DogHead::~DogHead()
{
	delete EnergyBalls;
	delete Controller;
}

void DogHead::Init()
{
	OriginLocation = Vector2(WIN_CENTER_X + 300, WIN_CENTER_Y + 100);
	Location = OriginLocation;

	MaxStat = CharacterStatus(100.0f, 50.0f, 20.0f, 0.0f);
	CurStat = MaxStat;
	
	Controller = new DogHeadAIController(this, &CurState);

	CollisionSetting();
	AnimationSetting();
	AnimStateSetting();
	TimerFunctionSetting();
	AISetting();

	//Controller->AddPatterns()

	TimerFunc timerFunction;
	timerFunction = TimerFunc(L"OnThrowBall", bind(&DogHead::OnThrowCharging, this), 4.0f, false, false);
	TimerManager::Get()->AddFunction(timerFunction);
	timerFunction = TimerFunc(L"OnFallBall", bind(&DogHead::OnFallCharging, this), 4.0f, false, false);
	TimerManager::Get()->AddFunction(timerFunction);
	timerFunction = TimerFunc(L"DashMove", bind(&DogHead::DashMove, this), 1.f, true, false);
	TimerManager::Get()->AddFunction(timerFunction);
	timerFunction = TimerFunc(L"EndDash", bind(&DogHead::EndDash, this), 1.f, false, false);
	TimerManager::Get()->AddFunction(timerFunction);

	//CurState = Dash_L;
	//SaveState = Glave_L;
	//
	////TimerManager::Get()->CallFunction(L"DashMove");
	////TimerManager::Get()->CallFunction(L"EndDash");
	//Anim->Play(CurState);

	//CurState = DownCharge_L;
	//TimerManager::Get()->CallFunction(L"OnFallBall");
	//Anim->Play(CurState);
	
	//CurState = Idle_L;
	//Anim->Play(CurState);
	
	//CurWeapon = new Weapon(this);

	EnergyBalls = new EnergyBallPolling(50, this, 2.0f);
}

void DogHead::Update()
{
	Super::Update();
	Controller->Update();
	//
	SetState();

	Vector2 camLocation = Camera::Get()->GetLocation();
	Location = OriginLocation - camLocation;

	if (OriginLocation.x < Target->GetLocation().x)
		CurDir = Right;
	else
		CurDir = Left;
	
	AnimationPlay();
	Anim->Update();
}

void DogHead::Render(HDC hdc)
{
	Super::Render(hdc);
	Anim->Render(hdc);

	wstring str;
	str = L"DogHead : " + to_wstring(CurStat.GetHealth());
	TextOut(hdc, WIN_WIDTH - 110, 0, str.c_str(), str.size());
}

void DogHead::OnBegin(RectCollision* Other)
{
	
}

void DogHead::AnimationSetting()
{
	std::wstring str;
	SpriteInfo sprite;

	str = L"Resource/Monster/DogHead/DogHead_R.bmp";
	sprite = SpriteInfo(str, Vector2(5000, 5000), Vector2(10, 10), 98, Vector2(-7, -20));
	Anim->Add(L"Motion_R", sprite);

	str = L"Resource/Monster/DogHead/DogHead_L.bmp";
	sprite = SpriteInfo(str, Vector2(5000, 5000), Vector2(10, 10), 98, Vector2(-7, -20));
	Anim->Add(L"Motion_L", sprite);
}

void DogHead::AnimStateSetting()
{
	// Right Motion
	//{
	//	Anim->SetFrame(L"Motion_R", State::Idle_R, Vector2(0, 0), Vector2(7, 0), LoopType::Loop);
	//	Anim->SetFrame(L"Motion_R", State::Move_R, Vector2(8, 0), Vector2(5, 1), LoopType::Loop);
	//	Anim->SetFrame(L"Motion_R", State::Hit_R, Vector2(6, 1), Vector2(7, 1), LoopType::Stop);
	//	Anim->SetFrame(L"Motion_R", State::Groggy_R, Vector2(8, 1), Vector2(2, 2), LoopType::Loop);
	//	Anim->SetFrame(L"Motion_R", State::GroggyEnd_R, Vector2(3, 2), Vector2(4, 2), LoopType::Stop);
	//	Anim->SetFrame(L"Motion_R", State::ThrowCharge_R, Vector2(5, 2), Vector2(8, 2), LoopType::Loop);
	//	Anim->SetFrame(L"Motion_R", State::ThrowEnd_R, Vector2(9, 2), Vector2(5, 3), LoopType::Stop);
	//	Anim->SetFrame(L"Motion_R", State::Dash_R, Vector2(6, 3), Vector2(6, 3), LoopType::Loop);
	//
	//	Anim->SetFrame(L"Motion_R", State::Hook_R, Vector2(9, 4), Vector2(0, 6), LoopType::Stop);
	//	Anim->SetFrame(L"Motion_R", State::Glave_R, Vector2(1, 6), Vector2(9, 6), LoopType::Stop);
	//	Anim->SetFrame(L"Motion_R", State::Spear_R, Vector2(0, 7), Vector2(8, 7), LoopType::Stop);
	//
	//	Anim->SetFrame(L"Motion_R", State::Domerta_R, Vector2(0, 8), Vector2(6, 8), LoopType::Loop);
	//	Anim->SetFrame(L"Motion_R", State::Pendeta_R, Vector2(7, 8), Vector2(8, 9), LoopType::Stop);
	//}
	{
		Anim->SetFrame(L"Motion_R", State::Idle_R, Vector2(0, 0), Vector2(7, 0), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Motion_R", State::Move_R, Vector2(8, 0), Vector2(5, 1), LoopType::Loop, 0.07f);
		Anim->SetFrame(L"Motion_R", State::Hit_R, Vector2(6, 1), Vector2(7, 1), LoopType::Delay, 0.1f);
		Anim->SetEndFunction(L"Motion_R", State::Hit_R, bind(&DogHead::ChangeIdleState, this));
		Anim->SetDelayTime(L"Motion_R", State::Hit_R, 0.5f);

		Anim->SetFrame(L"Motion_R", State::Groggy_R, Vector2(8, 1), Vector2(1, 2), LoopType::Loop, 0.2f);
		Anim->SetFrame(L"Motion_R", State::GroggyEnd_R, Vector2(2, 2), Vector2(4, 2), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_R", State::GroggyEnd_R, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_R", State::ThrowCharge_R, Vector2(5, 2), Vector2(8, 2), LoopType::Loop, 0.03f);
		//Anim->AddFrameFunction(L"Motion_R", State::ThrowCharge_R, 1, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::ThrowCharge_R, 0, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::ThrowCharge_R, 1, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::ThrowCharge_R, 2, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::ThrowCharge_R, 3, bind(&DogHead::OnThrowBall, this));

		Anim->SetFrame(L"Motion_R", State::ThrowEnd_R, Vector2(9, 2), Vector2(5, 3), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_R", State::ThrowEnd_R, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_R", State::DownCharge_R, Vector2(0, 8), Vector2(7, 8), LoopType::Loop, 0.05f);
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 0, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 1, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 2, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 3, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 4, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 5, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 6, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 7, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_R", State::DownCharge_R, 8, bind(&DogHead::OnFallingBall, this));

		Anim->SetFrame(L"Motion_R", State::DownEnd_R, Vector2(9, 2), Vector2(5, 3), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_R", State::DownEnd_R, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_R", State::Dash_R, Vector2(6, 3), Vector2(6, 3), LoopType::Loop);
		//Anim->AddFrameFunction(L"Motion_R", State::Dash_R, 0, bind(&DogHead::SetTargetDirection, this));

		Anim->SetFrame(L"Motion_R", State::Hook_R, Vector2(9, 4), Vector2(0, 6), LoopType::Stop, 0.1f);
		Anim->AddFrameFunction(L"Motion_R", State::Hook_R, 4, bind(&DogHead::HookMove, this));
		Anim->AddFrameFunction(L"Motion_R", State::Hook_R, 5, bind(&DogHead::HookMove, this));
		Anim->AddFrameFunction(L"Motion_R", State::Hook_R, 6, bind(&DogHead::HookMove, this));
		Anim->AddFrameFunction(L"Motion_R", State::Hook_R, 7, bind(&DogHead::HookMove, this));
		Anim->SetEndFunction(L"Motion_R", State::Hook_R, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_R", State::Glave_R, Vector2(1, 6), Vector2(9, 6), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_R", State::Glave_R, bind(&DogHead::ChangeIdleState, this));
		Anim->SetFrame(L"Motion_R", State::Spear_R, Vector2(1, 7), Vector2(8, 7), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_R", State::Spear_R, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_R", State::Domerta_R, Vector2(0, 8), Vector2(6, 8), LoopType::Loop);
		Anim->SetFrame(L"Motion_R", State::Pendeta_R, Vector2(7, 8), Vector2(8, 9), LoopType::Stop);
	}

	// Left Motion
	{
		Anim->SetFrame(L"Motion_L", State::Idle_L, Vector2(0, 0), Vector2(7, 0), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Motion_L", State::Move_L, Vector2(8, 0), Vector2(5, 1), LoopType::Loop, 0.07f);
		Anim->SetFrame(L"Motion_L", State::Hit_L, Vector2(6, 1), Vector2(7, 1), LoopType::Delay, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::Hit_L, bind(&DogHead::ChangeIdleState, this));
		Anim->SetDelayTime(L"Motion_L", State::Hit_L, 0.5f);

		Anim->SetFrame(L"Motion_L", State::Groggy_L, Vector2(8, 1), Vector2(1, 2), LoopType::Loop, 0.2f);
		Anim->SetFrame(L"Motion_L", State::GroggyEnd_L, Vector2(2, 2), Vector2(4, 2), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::GroggyEnd_L, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_L", State::ThrowCharge_L, Vector2(5, 2), Vector2(8, 2), LoopType::Loop, 0.03f);
		//Anim->AddFrameFunction(L"Motion_L", State::ThrowCharge_L, 1, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::ThrowCharge_L, 0, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::ThrowCharge_L, 1, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::ThrowCharge_L, 2, bind(&DogHead::OnThrowBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::ThrowCharge_L, 3, bind(&DogHead::OnThrowBall, this));
		
		Anim->SetFrame(L"Motion_L", State::ThrowEnd_L, Vector2(9, 2), Vector2(5, 3), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::ThrowEnd_L, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_L", State::DownCharge_L, Vector2(0, 8), Vector2(7, 8), LoopType::Loop, 0.05f);
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 0, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 1, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 2, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 3, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 4, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 5, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 6, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 7, bind(&DogHead::OnFallingBall, this));
		Anim->AddFrameFunction(L"Motion_L", State::DownCharge_L, 8, bind(&DogHead::OnFallingBall, this));

		Anim->SetFrame(L"Motion_L", State::DownEnd_L, Vector2(9, 2), Vector2(5, 3), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::DownEnd_L, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_L", State::Dash_L, Vector2(6, 3), Vector2(6, 3), LoopType::Loop);
		//Anim->AddFrameFunction(L"Motion_L", State::Dash_L, 0, bind(&DogHead::SetTargetDirection, this));

		Anim->SetFrame(L"Motion_L", State::Hook_L, Vector2(9, 4), Vector2(0, 6), LoopType::Stop, 0.1f);
		Anim->AddFrameFunction(L"Motion_L", State::Hook_L, 4, bind(&DogHead::HookMove, this));
		Anim->AddFrameFunction(L"Motion_L", State::Hook_L, 5, bind(&DogHead::HookMove, this));
		Anim->AddFrameFunction(L"Motion_L", State::Hook_L, 6, bind(&DogHead::HookMove, this));
		Anim->AddFrameFunction(L"Motion_L", State::Hook_L, 7, bind(&DogHead::HookMove, this));
		Anim->SetEndFunction(L"Motion_L", State::Hook_L, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_L", State::Glave_L, Vector2(1, 6), Vector2(9, 6), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::Glave_L, bind(&DogHead::ChangeIdleState, this));
		Anim->SetFrame(L"Motion_L", State::Spear_L, Vector2(1, 7), Vector2(8, 7), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::Spear_L, bind(&DogHead::ChangeIdleState, this));

		Anim->SetFrame(L"Motion_L", State::Domerta_L, Vector2(0, 8), Vector2(6, 8), LoopType::Loop);
		Anim->SetFrame(L"Motion_L", State::Pendeta_L, Vector2(7, 8), Vector2(8, 9), LoopType::Stop);
	}
}

void DogHead::AnimationPlay()
{
	if (BeforeState != CurState)
		Anim->Play(CurState);

	BeforeState = CurState;
	bChangeState = true;
}

void DogHead::AISetting()
{
	vector<int> patterns;
	patterns.push_back(Spear_R);
	patterns.push_back(Glave_R);
	patterns.push_back(Hook_R);
	Controller->AddPatterns(patterns);
	patterns.clear();
	patterns.push_back(DownCharge_R);
	patterns.push_back(ThrowCharge_R);
	Controller->AddPatterns(patterns);
	patterns.clear();
}

void DogHead::TimerFunctionSetting()
{
	TimerFunc timerFunction = TimerFunc(L"GroggyEnd", bind(&DogHead::ChangeGroggyEndState, this), 3.0f, false, false);
	TimerManager::Get()->AddFunction(timerFunction);
}

void DogHead::OnDeath()
{
	IsActive = false;
}

void DogHead::OnGroggy()
{
	CurState = Groggy_L;
	TimerManager::Get()->CallFunction(L"GroggyEnd");
}

void DogHead::OnThrowCharging()
{
	if (CurDir == Left)
		CurState = ThrowEnd_L;
	else
		CurState = ThrowEnd_R;
}

void DogHead::OnFallCharging()
{
	if (CurDir == Left)
		CurState = DownEnd_L;
	else
		CurState = DownEnd_R;
}

void DogHead::OnFallingBall()
{
	ShootInterval += DELTA_TIME;

	if (ShootInterval <= THROW_INTERVAL) return;
	ShootInterval = 0.0f;

	EnergyBalls->SetLocation(Target->GetLocation());
	EnergyBalls->OnShoot(200.0f);
}

void DogHead::OnThrowBall()
{
	ShootInterval += DELTA_TIME;

	if (ShootInterval <= THROW_INTERVAL) return;
	ShootInterval = 0.0f;

	Vector2 location = Location;
	location.y -= 300.0f;
	
	location.x += GameMath::Random(-70, 70);
	location.y += GameMath::Random(-30, 30);

	EnergyBalls->SetLocation(location);
	EnergyBalls->OnShoot(Target->GetLocation());
}

void DogHead::SetState()
{
	if (bChangeState == true) return;
	
	if (CurDir == Left)
		CurState += 18;
	
	if (CurState == Spear_R || CurState == Spear_L ||
		CurState == Glave_R || CurState == Glave_L ||
		CurState == Hook_R || CurState == Hook_L)
	{
		SaveState = CurState;
		CurState = Dash_R;
	
		SetTargetDirection();
		//TimerManager::Get()->CallFunction(L"DashMove");
		
		if (CurDir == Left)
			CurState += 18;
	}
	
	else if (CurState == DownCharge_L || CurState == DownCharge_R)
	{
		TimerManager::Get()->CallFunction(L"OnFallBall");
	}
	else if (CurState == ThrowCharge_L || CurState == ThrowCharge_R)
	{
		TimerManager::Get()->CallFunction(L"OnThrowBall");
	}
}

void DogHead::CollisionSetting()
{
	CollisionManager::Get()->ChangeCollisionChannel(Collision, CollisionChannel::Channel1);
	Collision->SetHidden(false);

	Collision->SetLocation(OriginLocation);
	
	Collision->SetSize(Vector2(60.0f, 140.0f));
	Collision->SetHidden(false);

	Collision->AddFunction(Implement<DogHead>(this, &DogHead::OnBegin));
}

void DogHead::ChangeIdleState()
{
	if (CurDir == Left)
		CurState = Idle_L;
	else
		CurState = Idle_R;

	Controller->CompliteAction();
	bChangeState = false;
}

void DogHead::ChangeGroggyEndState()
{
	if (CurDir == Left)
		CurState = GroggyEnd_L;
	else
		CurState = GroggyEnd_R;
}

void DogHead::SetTargetDirection()
{
	float top = Target->GetCollision()->Top();
	float bottom = Target->GetCollision()->Bottom();
	(bottom - top) * 0.5f;

	GetCollision()->Top();
	GetCollision()->Bottom();

	Vector2 targetLocation = Target->GetLocation();
	Vector2 camLocation = Camera::Get()->GetLocation();

	MoveDir = targetLocation + camLocation;

	TimerManager::Get()->CallFunction(L"DashMove");
	TimerManager::Get()->CallFunction(L"EndDash");
}

void DogHead::DashMove()
{
	Vector2 direction = MoveDir - Location;

	float distance = direction.Length() - 50.0f;
	direction.Normalize();

	if (distance > 10.0f)
		OriginLocation += direction * (distance * 1.5f) * DELTA_TIME;
}

void DogHead::EndDash()
{
	CurState = SaveState;
}

void DogHead::HookMove()
{
	Vector2 direction = MoveDir - Location;

	float distance = direction.Length();
	direction.Normalize();

	if (distance > 10.0f)
		OriginLocation += direction * (distance * 1.5f) * DELTA_TIME;
}

void DogHead::EndHook()
{
}

void DogHead::SpearMove()
{
}

void DogHead::EndSpear()
{
}

void DogHead::GlaveMove()
{
}

void DogHead::EndGlave()
{
}
