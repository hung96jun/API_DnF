#include "Framework/Framework.h"
#include "Goblin.h"

Goblin::Goblin()
{
}

Goblin::~Goblin()
{
}

void Goblin::Init()
{
	CurState = State::Idle_R;

	Collision->AddFunction(Implement<Goblin>(this, &Goblin::OnBegin));
}

void Goblin::Update()
{
	Super::Update();

	Collision->AddFunction(Implement<Goblin>(this, &Goblin::OnBegin));
}

void Goblin::Render(HDC hdc)
{
	Super::Render(hdc);

}

void Goblin::FiniteStateMachine()
{
	if (Target == nullptr) return;
}

void Goblin::OnBegin(RectCollision* Other)
{
}

void Goblin::AnimationSetting()
{
	std::wstring str;
	SpriteInfo sprite;

	{
		str = L"Resource/Monster/Goblin/Goblin_R.bmp";
		sprite = SpriteInfo(str, Vector2(648, 568), Vector2(6, 4), 23, Vector2());
		Anim->Add(L"Motion_R", sprite);

		str = L"Resource/Monster/Goblin/Goblin_L.bmp";
		sprite = SpriteInfo(str, Vector2(648, 568), Vector2(6, 4), 23, Vector2());
		Anim->Add(L"Motion_L", sprite);
	}
}

void Goblin::AnimStateSetting()
{
	// Right Motion
	{
		Anim->SetFrame(L"Movement_R", State::Idle_R, Vector2(0, 0), Vector2(0, 0), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_R", State::Move_R, Vector2(0, 1), Vector2(5, 1), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_R", State::Attack_R, Vector2(0, 2), Vector2(3, 2), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_R", State::Hit_R, Vector2(1, 3), Vector2(1, 3), LoopType::Loop, 0.5f);
		Anim->SetFrame(L"Movement_R", State::Death_R, Vector2(1, 3), Vector2(5, 3), LoopType::Loop, 0.05f);
	}

	// Left Motion
	{
		Anim->SetFrame(L"Movement_L", State::Idle_L, Vector2(0, 0), Vector2(0, 0), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_L", State::Move_L, Vector2(0, 1), Vector2(5, 1), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_L", State::Attack_L, Vector2(0, 2), Vector2(3, 2), LoopType::Loop, 0.1f);
		Anim->SetFrame(L"Movement_L", State::Hit_L, Vector2(1, 3), Vector2(1, 3), LoopType::Loop, 0.5f);
		Anim->SetFrame(L"Movement_L", State::Death_L, Vector2(1, 3), Vector2(5, 3), LoopType::Loop, 0.05f);
	}
}

void Goblin::AnimationPlay()
{
	if (BeforeState != CurState)
		Anim->Play(CurState);

	BeforeState = CurState;
}
