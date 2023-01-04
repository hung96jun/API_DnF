#pragma once

class PollingSystem
{
public:
	PollingSystem() = default;
	PollingSystem(const UINT& MaxCount);
	~PollingSystem();
	
	void Update();
	void Render(HDC hdc);

protected:
	vector<Actor*> TotalObject;
};