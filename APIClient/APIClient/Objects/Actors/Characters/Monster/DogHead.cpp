#include "Framework/Framework.h"
#include "DogHead.h"

DogHead::DogHead()
{
	Init();
}

DogHead::~DogHead()
{
}

void DogHead::Update()
{
	Super::Update();

	Vector2 camLocation = Camera::Get()->GetLocation();
	Location = OriginLocation - camLocation;

	Anim->Update();

	AnimationPlay();
}

void DogHead::Render(HDC hdc)
{
	Super::Render(hdc);
	Anim->Render(hdc);
}

void DogHead::Init()
{
	OriginLocation = Vector2(WIN_CENTER_X + 100, WIN_CENTER_Y + 100);
	Location = OriginLocation;

	//CollisionSetting();
	AnimationSetting();
	AnimStateSetting();
	TimerFunctionSetting();

	CurState = ThrowCharge_L;
	Anim->Play(CurState);
	
	Collision->SetSize(Vector2(30, 100));

	TimerFunc timerFunction = TimerFunc(L"OnThrowBall", bind(&DogHead::OnThrowCharging, this), 4.0f, false, false);
	TimerManager::Get()->AddFunction(timerFunction);

	TimerManager::Get()->CallFunction(L"OnThrowBall");
}

void DogHead::OnBegin(RectCollision* Other)
{
}

void DogHead::AnimationSetting()
{
	std::wstring str;
	SpriteInfo sprite;

	str = L"Resource/Monster/DogHead/DogHead_R.bmp";
	sprite = SpriteInfo(str, Vector2(5000, 5000), Vector2(10, 10), 98, Vector2());
	Anim->Add(L"Motion_R", sprite);

	str = L"Resource/Monster/DogHead/DogHead_L.bmp";
	sprite = SpriteInfo(str, Vector2(5000, 5000), Vector2(10, 10), 98, Vector2());
	Anim->Add(L"Motion_L", sprite);
}

void DogHead::AnimStateSetting()
{
	// Right Motion
	{
		Anim->SetFrame(L"Motion_R", State::Idle_R, Vector2(0, 0), Vector2(7, 0), LoopType::Loop);
		Anim->SetFrame(L"Motion_R", State::Move_R, Vector2(8, 0), Vector2(5, 1), LoopType::Loop);
		Anim->SetFrame(L"Motion_R", State::Hit_R, Vector2(6, 1), Vector2(7, 1), LoopType::Stop);
		Anim->SetFrame(L"Motion_R", State::Groggy_R, Vector2(8, 1), Vector2(2, 2), LoopType::Loop);
		Anim->SetFrame(L"Motion_R", State::GroggyEnd_R, Vector2(3, 2), Vector2(4, 2), LoopType::Stop);
		Anim->SetFrame(L"Motion_R", State::ThrowCharge_R, Vector2(5, 2), Vector2(8, 2), LoopType::Loop);
		Anim->SetFrame(L"Motion_R", State::ThrowEnd_R, Vector2(9, 2), Vector2(5, 3), LoopType::Stop);
		Anim->SetFrame(L"Motion_R", State::Dash_R, Vector2(6, 3), Vector2(6, 3), LoopType::Loop);

		Anim->SetFrame(L"Motion_R", State::Hook_R, Vector2(9, 4), Vector2(0, 6), LoopType::Stop);
		Anim->SetFrame(L"Motion_R", State::Glave_R, Vector2(1, 6), Vector2(9, 6), LoopType::Stop);
		Anim->SetFrame(L"Motion_R", State::Spear_R, Vector2(0, 7), Vector2(8, 7), LoopType::Stop);

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
		Anim->AddFrameFunction(L"Motion_L", State::ThrowCharge_L, 1, bind(&DogHead::OnThrowBall, this));
		Anim->SetFrame(L"Motion_L", State::ThrowEnd_L, Vector2(9, 2), Vector2(5, 3), LoopType::Stop, 0.1f);
		Anim->SetEndFunction(L"Motion_L", State::ThrowEnd_L, bind(&DogHead::ChangeIdleState, this));
		Anim->SetFrame(L"Motion_L", State::Dash_L, Vector2(6, 3), Vector2(6, 3), LoopType::Loop);
								
		Anim->SetFrame(L"Motion_L", State::Hook_L, Vector2(9, 4), Vector2(0, 6), LoopType::Stop);
		Anim->SetFrame(L"Motion_L", State::Glave_L, Vector2(1, 6), Vector2(9, 6), LoopType::Stop);
		Anim->SetFrame(L"Motion_L", State::Spear_L, Vector2(0, 7), Vector2(8, 7), LoopType::Stop);
								
		Anim->SetFrame(L"Motion_L", State::Domerta_L, Vector2(0, 8), Vector2(6, 8), LoopType::Loop);
		Anim->SetFrame(L"Motion_L", State::Pendeta_L, Vector2(7, 8), Vector2(8, 9), LoopType::Stop);
	}
}

void DogHead::AnimationPlay()
{
	if (BeforeState != CurState)
		Anim->Play(CurState);

	BeforeState = CurState;
}

void DogHead::TimerFunctionSetting()
{
	TimerFunc timerFunction = TimerFunc(L"GroggyEnd", bind(&DogHead::ChangeGroggyEndState, this), 3.0f, false, false);
	TimerManager::Get()->AddFunction(timerFunction);
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

void DogHead::OnThrowBall()
{

}

void DogHead::ChangeIdleState()
{
	if (CurDir == Left)
		CurState = Idle_L;
	else
		CurState = Idle_R;
}

void DogHead::ChangeGroggyEndState()
{
	if (CurDir == Left)
		CurState = GroggyEnd_L;
	else
		CurState = GroggyEnd_R;
}
