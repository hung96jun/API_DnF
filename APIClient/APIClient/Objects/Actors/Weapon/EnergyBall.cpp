#include "Framework/Framework.h"
#include "EnergyBall.h"

EnergyBall::EnergyBall()
{
	OriginLocation = { WIN_CENTER_X, WIN_CENTER_Y };
	Location = OriginLocation;

	Anim = new Animation(this);

	AnimationSetting();

	IsActive = true;
	Anim->Play(0);
}

EnergyBall::~EnergyBall()
{
	delete Anim;
}

void EnergyBall::Update()
{
	if (IsActive == false) return;

	Vector2 camLocation = Camera::Get()->GetLocation();
	Location = OriginLocation - camLocation;
	//Location += Direction * (SPEED * DELTA_TIME);
	Anim->Update();
}

void EnergyBall::Render(HDC hdc)
{
	if (IsActive == false) return;
	Anim->Render(hdc);
	//Anim->Render(hdc, 200);
}

void EnergyBall::Play(Vector2 Target)
{
	float min = Target.x - THROW_RANGE;
	float max = Target.x + THROW_RANGE;

	Direction.x = GameMath::Random(min, max);
	
	min = Target.y - THROW_RANGE;
	max = Target.y + THROW_RANGE;

	Direction.y = GameMath::Random(min, max);
	Anim->Play(0);
}

void EnergyBall::Play()
{
}

void EnergyBall::AnimationSetting()
{
	std::wstring str;
	SpriteInfo sprite;

	str = L"Resource/EnergeBall2.bmp";
	sprite = SpriteInfo(str, Vector2(500, 500), Vector2(4, 4), 8, Vector2(0, 0));// , RGB(241, 0, 255));
	Anim->Add(L"Play", sprite);
	Anim->SetFrame(L"Play", 0, Vector2(0, 0), Vector2(1, 3), LoopType::Loop, 0.1f);
}

void EnergyBall::OnBegin(RectCollision* Other)
{
}
