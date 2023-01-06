#pragma once

class AIController
{
public:
	AIController() = default;
	AIController(Character* Owner, int* State);
	~AIController();

	virtual void Update();

	void AddPatterns(std::vector<int> OnePattern) { MaxPatterns.push_back(OnePattern); }

	virtual void Excute();
	virtual void CompliteAction();

	virtual void SelectAction() {}

protected:
	bool IsExcute = false;

	std::vector<std::vector<int>> MaxPatterns;
	std::queue<int> CurPattern;
	int* OwnerState = nullptr;

	Character* Owner = nullptr;
};