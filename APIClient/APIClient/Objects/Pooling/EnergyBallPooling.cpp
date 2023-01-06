#include "Framework/Framework.h"
#include "EnergyBallPooling.h"


EnergyBallPolling::EnergyBallPolling(const UINT& MaxCount, Character* Owner, const float& DamageMagnification)
	:PollingSystem(MaxCount)
{
	for (int i = 0; i < MaxCount; ++i)
	{
		EnergyBall* ball = new EnergyBall(Owner);
		TotalObjects.push_back(ball);
		ball->SetDamage(DamageMagnification);
	}
}

EnergyBallPolling::~EnergyBallPolling()
{
}

void EnergyBallPolling::SetLocation(const Vector2& Location)
{
	static_cast<EnergyBall*>(TotalObjects[Index])->SetLocation(Location);
}

void EnergyBallPolling::OnShoot(const Vector2 Target)
{
	static_cast<EnergyBall*>(TotalObjects[Index])->OnShoot(Target);
	++Index;
	Index %= MAX_SIZE;
}

void EnergyBallPolling::OnShoot(const float& Height)
{
	static_cast<EnergyBall*>(TotalObjects[Index])->OnShoot(Height);
	++Index;
	Index %= MAX_SIZE;
}

