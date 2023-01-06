#pragma once

class PollingSystem
{
<<<<<<< HEAD
protected:
	const UINT MAX_SIZE = 0;
public:
	PollingSystem() = default;
	PollingSystem(const UINT& MaxCount);
	virtual ~PollingSystem();
	
protected:
	std::vector<Actor*> TotalObjects;
=======
public:
	PollingSystem() = default;
	PollingSystem(const UINT& MaxCount);
	~PollingSystem();
	
	void Update();
	void Render(HDC hdc);

protected:
	vector<Actor*> TotalObject;
>>>>>>> c8e04d29f87ba0ecdf7f31d030b30992ada9642c
};