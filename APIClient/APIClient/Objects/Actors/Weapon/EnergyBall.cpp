#include "Framework/Framework.h"
#include "EnergyBall.h"

EnergyBall::EnergyBall(Character* Owner)
	:Weapon(Owner)
{
	float x = GameMath::Random(-100, 100);
	float y = GameMath::Random(-100, 100);
	OriginLocation = { WIN_CENTER_X + x - 200, WIN_CENTER_Y + y };
	Location = OriginLocation;

	Anim = new Animation(this);
	hDamage = new DamageHandle(this);

	AnimationSetting();

	IsActive = false;
	Anim->Play(0);

	TimerFunc timerFunction;
	timerFunction = TimerFunc(L"OnMove", bind(&EnergyBall::OnMove, this), 1.0f);
	TimerManager::Get()->AddFunction(timerFunction);

	CollisionSetting();
}

EnergyBall::~EnergyBall()
{
	//delete Anim;
	Owner = nullptr;
	Anim = nullptr;
}

void EnergyBall::Update()
{
	if (IsActive == false) return;
	Super::Update();

	Vector2 camLocation = Camera::Get()->GetLocation();
	Location = OriginLocation - camLocation;

	Anim->Update();
	//if (bMove == false) return;

	Cur += TimerManager::Get()->GetElapsedTime();
	float test = Cur - Start;
	if (test < 1.0f) return;

	float dist = (OriginLocation - LandPoint).Length();
	if (dist < 10.0f)
		ChangeBoom();
	else
		OriginLocation += Direction * (SPEED * DELTA_TIME);
}

void EnergyBall::Render(HDC hdc)
{
	if (IsActive == false) return;
	Super::Render(hdc);
	Anim->Render(hdc);
	//Anim->Render(hdc, 200);
}

void EnergyBall::SetLocation(const Vector2& Location)
{
	Vector2 camLocation = Camera::Get()->GetLocation();

	this->OriginLocation = Location + camLocation;
}

void EnergyBall::OnShoot(const Vector2 Target)
{
	IsActive = true;
	CurState = Fall;
	Anim->Play(0);

	LandPoint = Target + Camera::Get()->GetLocation();
	Direction = LandPoint - OriginLocation;

	Direction.Normalize();

	Start = TimerManager::Get()->GetElapsedTime();
	Cur = Start;
}

void EnergyBall::OnShoot(const float& Height)
{
	IsActive = true;
	CurState = Fall;
	Anim->Play(0);

	float height = Height;

	OriginLocation.y -= height;

	Location.y -= Height;

	Direction.x = 0.0f;
	Direction.y = 1.0f;
	Direction.Normalize();

	LandPoint.x = OriginLocation.x;
	LandPoint.y = OriginLocation.y + height;

	Start = TimerManager::Get()->GetElapsedTime();
	Cur = Start;
}

void EnergyBall::AnimationSetting()
{
	std::wstring str;
	SpriteInfo sprite;

	str = L"Resource/EnergeBall2.bmp";
	sprite = SpriteInfo(str, Vector2(500, 500), Vector2(4, 4), 8, Vector2(0, 0));// , RGB(241, 0, 255));
	Anim->Add(L"Play", sprite);
	Anim->SetFrame(L"Play", 0, Vector2(0, 0), Vector2(1, 3), LoopType::Loop, 0.1f);
	//Anim->SetEndFunction(L"Play", 0, bind(&EnergyBall::ChangeBoom, this));

	str = L"Resource/ExplosionPurple.bmp";
	sprite = SpriteInfo(str, Vector2(512, 256), Vector2(4, 2), 7, Vector2(0, 0), BLACK);// , RGB(241, 0, 255));
	Anim->Add(L"Boom", sprite);
	Anim->SetFrame(L"Boom", 1, Vector2(0, 0), Vector2(3, 1), LoopType::Stop, 0.1f);
	Anim->SetEndFunction(L"Boom", 1, bind(&EnergyBall::End, this));
}

void EnergyBall::ChangeBoom()
{
	if (CurState != Fall) return;

	CurState = Boom;
	Anim->Play(1);

	Collision->SetActive(true);
}

void EnergyBall::End()
{
	Collision->SetActive(false);
	IsActive = false;
}

void EnergyBall::CollisionSetting()
{
	Collision->SetSize(Vector2(90.0, 90.0f));
	Collision->SetHidden(false);

	Collision->AddFunction(Implement<EnergyBall>(this, &EnergyBall::OnBegin));
}

void EnergyBall::OnBegin(RectCollision* Other)
{
	if (Other->GetOwner() == Owner) return;

	hDamage->GiveDamage(static_cast<Character*>(Other->GetOwner()), Damage);
}

void EnergyBall::SetDamage(const float& DamageMagnification)
{
	Damage = Owner->GetCurStatus().GetDamage();
	Damage *= DamageMagnification;
}
