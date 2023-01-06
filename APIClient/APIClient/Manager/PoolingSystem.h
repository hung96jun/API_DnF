#pragma once

class PollingSystem
{
protected:
	const UINT MAX_SIZE = 0;
public:
	PollingSystem() = default;
	PollingSystem(const UINT& MaxCount);
	virtual ~PollingSystem();
	
protected:
	std::vector<Actor*> TotalObjects;
};