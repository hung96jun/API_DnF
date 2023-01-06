#pragma once

class EnergyBallPolling : public PollingSystem
{
public:
	EnergyBallPolling() = default;
	EnergyBallPolling(const UINT& MaxCount, Character* Owner, const float& DamageMagnification);
	virtual ~EnergyBallPolling() override;

	void SetLocation(const Vector2& Location);

	void OnShoot(const Vector2 Target);
	void OnShoot(const float& Height);

private:
	UINT Index = 0;
};